#include "LevelPrototype.h"
#include "CollisionHandler.h"

void LevelPrototype::levelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->loadData();
	GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

	SquareBorderMesh* border = new SquareBorderMesh();
	border->loadData();
	GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);

	//cout << "Load Level" << endl;
}

void LevelPrototype::levelInit() {
	Player* player_ = new Player(10);
	objectsList.push_back(player_);
	player = player_;
	player->setLevel(this);

	objectsList.push_back(player->getGroundChecker()); // Add groundChecker

	bow = player->getBow();
	if (bow) {
		for (DrawableObject* obj : bow->getChainAttackList()) {
			BowUltimateCollider* col = dynamic_cast<BowUltimateCollider*>(obj);
			col->setPlayer(player);
			objectsList.push_back(obj);
		}
	}

	sword = player->getSword();
	if (sword) {
		for (DrawableObject* obj : sword->getChainAttackList()) {
			PlayerAttackCollider* col = dynamic_cast<PlayerAttackCollider*>(obj);
			//cout << col->getName() << endl;
			col->setPlayer(player);
			objectsList.push_back(obj);
		}
	}

	shield = player->getShield();
	if (shield) {
		for (DrawableObject* obj : shield->getChainAttackList()) {
			PlayerAttackCollider* col = dynamic_cast<PlayerAttackCollider*>(obj);
			col->setPlayer(player);
			objectsList.push_back(obj);
		}
	}

	Enemy* enemy_ = new Enemy(10);
	objectsList.push_back(enemy_);
	objectsList.push_back(enemy_->getEnemyAttackCollider());
	enemy = enemy_;

	SimpleObject* floor = new SimpleObject();
	floor->getTransform().setPosition(glm::vec3(0.0f, -2.5f, 0.0f));
	floor->getTransform().setScale(glm::vec3(18.0f, 1.0f, 0.0f));
	floor->addColliderComponent();
	floor->setName("Floor");
	floor->setTag(Tag::Floor);
	floor->setDrawCollider(true);
	objectsList.push_back(floor);

	//cout << "Init Level" << endl;
}

void LevelPrototype::levelUpdate() {
	dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	timeK += dt;

	player->getStateMachine()->update(player, dt);

	updateObjects(objectsList);

	for (DrawableObject* obj : objectsList) {

		Enemy* enemy = dynamic_cast<Enemy*>(obj);
		if (enemy) {
			if (enemy->getEnemyAttackCollider()) {
				// Update attackCollider to follow enemy
				enemy->getEnemyAttackCollider()->getTransform().setPosition(enemy->getTransform().getPosition());
			}

			enemy->selfUpdate(dt);
		}

		Arrow* arrow = dynamic_cast<Arrow*>(obj);
		if (arrow) {
			if (arrow->getFacingDirection()) {
				arrow->getTransform().translate(glm::vec3(arrow->getArrowSpeed() * dt, 0, 0));
			}
			else {
				arrow->getTransform().translate(glm::vec3(-arrow->getArrowSpeed() * dt, 0, 0));
			}

			arrow->selfUpdate(dt);
		}

		BowUltimateCollider* attackCollider = dynamic_cast<BowUltimateCollider*>(obj);
		if (attackCollider) {
			attackCollider->update(dt);
		}
	}
	
	player->selfUpdate(dt);
	sword->update(dt, player);
	bow->update(dt, player);
	shield->update(dt, player);

	//for (DrawableObject* obj : objectsList) { //Update enemy object
	//	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	//	if (enemy && enemy->getEnemyAttackCollider()) {
	//		// Update attackCollider to follow enemy
	//		enemy->getEnemyAttackCollider()->getTransform().setPosition(enemy->getTransform().getPosition());
	//	}
	//}

	player->getAnimationComponent()->updateCurrentState(dt);

	/*if (timeK > 0.12f) {
		player->getAnimationComponent()->updateCurrentState();
		d = 0;
		timeK = 0;
	}*/

	handleObjectCollision(objectsList);
}



void LevelPrototype::levelDraw() {
	GameEngine::getInstance()->render(objectsList);
	//cout << "Draw Level" << endl;
}

void LevelPrototype::levelFree() {
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	//cout << "Free Level" << endl;
}

void LevelPrototype::levelUnload() {
	GameEngine::getInstance()->clearMesh();
	//cout << "Unload Level" << endl;
}

void LevelPrototype::handleKey(char key) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float speed = 20.0f;
	speed *= dt;

	bool playerIsMoving = false;

	//Jump -> higher priority

	if (sword->getInChainAttack() || shield->getInChainAttack() || shield->getIsHolding() || bow->getIsShooting() || player->getIsDashing()) { //Prevent returning back to idle
		return;
	}

	switch (key) {
	case 'w':
		//player->getTransform().translate(glm::vec3(0, player->getMovementSpeed() * dt, 0));
		if (player->getIsGrounded()) {
			player->setIsGrounded(false);
			player->getPhysicsComponent()->setVelocity(glm::vec2(player->getPhysicsComponent()->getVelocity().x, 0.0f)); //Set y velocity to 0 before jump to ensure player jump at the same height every time
			player->getPhysicsComponent()->addForce(glm::vec2(0.0f, player->getJumpPower()));
		}
		//player->getAnimationComponent()->setState("up");
		break;
	case 's':
		//player->getTransform().translate(glm::vec3(0, -player->getMovementSpeed() * dt, 0));
		/*player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		playerIsMoving = true;*/
		//player->getAnimationComponent()->setState("down");
		break;
	case 'a':
		player->getPhysicsComponent()->setVelocity(glm::vec2(-player->getMovementSpeed(), player->getPhysicsComponent()->getVelocity().y));
		//player->getTransform().translate(glm::vec3(-player->getMovementSpeed() * dt, 0, 0));
		player->setFacingRight(false);

		if (player->getIsGrounded()) { // only change when walking on ground
			player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		}

		playerIsMoving = true;
		//player->getAnimationComponent()->setState("left");
		break;
	case 'd':
		player->getPhysicsComponent()->setVelocity(glm::vec2(player->getMovementSpeed(), player->getPhysicsComponent()->getVelocity().y));
		//player->getTransform().translate(glm::vec3(player->getMovementSpeed() * dt, 0, 0));
		player->setFacingRight(true);

		if (player->getIsGrounded()) {
			player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		}

		playerIsMoving = true;
		//player->getAnimationComponent()->setState("right");
		break;
	case 'q':
		if (player->getWeaponType() == Bow_) {
			//cout << "works" << endl;
			if (player->getUltimateSlot() > 0) {
				if (player->getUltimateSlot() < player->getUltimateSlotMax()) {
					player->increaseUltimateSlot(-1); //decrease ult slot by 1
					//enter small ult
					player->getStateMachine()->changeState(PlayerSmallBowUlt::getInstance(), player);
				}
				else {
					player->increaseUltimateSlot(-player->getUltimateSlotMax()); //decrease ult slot by max
					//enter big ult
					player->getStateMachine()->changeState(PlayerBigBowUlt::getInstance(), player);
				}
			}
		}
		else if (player->getWeaponType() == Sword_) {
			if (player->getUltimateSlot() > 0) {
				if (player->getUltimateSlot() < player->getUltimateSlotMax()) {
					player->increaseUltimateSlot(-1); //decrease ult slot by 1
					//enter small ult
					player->getStateMachine()->changeState(PlayerSmallSwordUlt::getInstance(), player);
				}
				else {
					player->increaseUltimateSlot(-player->getUltimateSlotMax()); //decrease ult slot by max
					//enter big ult
					player->getStateMachine()->changeState(PlayerBigSwordUlt::getInstance(), player);
				}
			}
		}
		else if (player->getWeaponType() == Shield_) {
			if (player->getUltimateSlot() > 0) {
				if (player->getUltimateSlot() < player->getUltimateSlotMax()) {
					player->increaseUltimateSlot(-1); //decrease ult slot by 1
					//enter small ult
					player->getStateMachine()->changeState(PlayerSmallShieldUlt::getInstance(), player);
				}
				else {
					player->increaseUltimateSlot(-player->getUltimateSlotMax()); //decrease ult slot by max
					//enter big ult
					player->getStateMachine()->changeState(PlayerBigShieldUlt::getInstance(), player);
				}
			}
		}
		break;
	case 'r': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART; ; break;
	case 'e': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_LEVEL2; ; break;
	case 'f': bow->setEnableDebug(); break;
	case 'h': player->setWeaponType(Bow_); break;
	case 'j': player->setWeaponType(Sword_); break;
	case 'g': player->setWeaponType(Shield_); cout << "Works" << endl; break;
	case 'I': //No Movement Input -> Idle
		if (player->getIsGrounded()) {
			player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
		}
		player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
		break;
	case 'S': //Spacebar -> Jump
		if (player->getIsGrounded()) {
			player->setIsGrounded(false);
			player->getPhysicsComponent()->setVelocity(glm::vec2(player->getPhysicsComponent()->getVelocity().x, 0.0f)); //Set y velocity to 0 before jump to ensure player jump at the same height every time
			player->getPhysicsComponent()->addForce(glm::vec2(0.0f, player->getJumpPower()));
		}
		break;
	case 'P':
		if (player->getCanDash()) {
			player->setMovementSpeed(player->getMovementSpeed() * 4);
			player->setIsDashing(true);
			player->setCanDash(false);
		}
		break;
	case 't':
		player->increaseUltimateSlot(1);
		break;
	}

	/*if (!playerIsMoving) {
		player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
	}*/
}

void LevelPrototype::handleMouse(int type, int x, int y) {
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;

	GameEngine::getInstance()->getWindowWidth();
	GameEngine::getInstance()->getWindowHeight();

	//cout << "X : " << realX << " Y : " << realY << endl;

	//Check player weapon
	// assume type = bow first

	if (player->getIsDashing()) { //Prevent returning
		return;
	}

	if (player->getWeaponType() == Bow_) {
		if (type == 0) {
			if (bow->getIsOverheat() == false) {
				if (bow->getRapidShotReady()) {
					/*DrawableObject* newArrow = bow->arrowShot(10, player, 25);
					objectsList.push_back(newArrow);*/
					player->getStateMachine()->changeState(PlayerLightBowAttack::getInstance(), player);
				}
			}
		}
		else if (type == 1) {
			/*DrawableObject* newArrow = bow->arrowShot(100, player, 50);
			objectsList.push_back(newArrow);*/
			player->getStateMachine()->changeState(PlayerHeavyBowAttack::getInstance(), player);
		}
	}
	else if (player->getWeaponType() == Sword_) {
		if (type == 0) {
			//enter first attack of the chain

			if (sword->getInChainAttack()) {
				//input buffer
				sword->setInputBuffer(true);
				return;
			}

			switch (sword->getCurrentChainAttack()) {
			case 0:
				player->getStateMachine()->changeState(PlayerLightSwordAttack1::getInstance(), player);
				break;
			/*case 1:
				player->getStateMachine()->changeState(PlayerLightSwordAttack2::getInstance(), player);
				break;
			case 2:
				player->getStateMachine()->changeState(PlayerLightSwordAttack3::getInstance(), player);
				break;*/
			}

			
		}
		else if (type == 1) {
			if (sword->getInChainAttack()) {
				return;
			}

			player->getStateMachine()->changeState(PlayerHeavySwordAttack::getInstance(), player);
		}

	}
	else if (player->getWeaponType() == Shield_) {
		if (type == 0) {
			//enter first attack of the chain

			if (shield->getInChainAttack()) {
				//input buffer
				shield->setInputBuffer(true);
				return;
			}

			switch (shield->getCurrentChainAttack()) {
			case 0:
				player->getStateMachine()->changeState(PlayerLightShieldAttack1::getInstance(), player);
				break;
				/*case 1:
					player->getStateMachine()->changeState(PlayerLightSwordAttack2::getInstance(), player);
					break;
				case 2:
					player->getStateMachine()->changeState(PlayerLightSwordAttack3::getInstance(), player);
					break;*/
			}


		}
		else if (type == 1) {
			if (shield->getInChainAttack()) {
				return;
			}

			player->getStateMachine()->changeState(PlayerShieldGuard::getInstance(), player);
		}
		else if (type == 3) {	

			if (shield->getIsBlocking()) {
				player->getStateMachine()->changeState(PlayerOffShield::getInstance(), player);
			}
		}
	}
	
	

	//player->getTransform().setPosition(glm::vec3(realX, realY, 0));
}

void LevelPrototype::handleAnalogStick(int type, float amount) {

	if (type == 0) {//x axis
		player->getTransform().translate(glm::vec3(0.3 * amount, 0, 0));
	}
	else if (type == 1) {//y axis
		player->getTransform().translate(glm::vec3(0, -0.3 * amount, 0));
	}
}

void LevelPrototype::addObject(DrawableObject* obj) {
	objectsList.push_back(obj);
}
