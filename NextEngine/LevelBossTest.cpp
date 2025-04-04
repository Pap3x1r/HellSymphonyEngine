#include "LevelBossTest.h"
#include "CollisionHandler.h"
#include "Bow.h"




void LevelBossTest::levelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->loadData();
	GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

	SquareBorderMesh* border = new SquareBorderMesh();
	border->loadData();
	GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);

	//cout << "Load Level" << endl;
}

void LevelBossTest::levelInit() {

	

	Player* player_ = new Player(100, 0, 3);
	objectsList.push_back(player_);
	player = player_;
	player->setLevel(this);
	player->getTransform().setPosition(glm::vec3(-5.0,2.0f,0.0f));
	objectsList.push_back(player->getGroundChecker());

	if (player->getBow()) {
		for (DrawableObject* obj : player->getBow()->getChainAttackList()) {
			BowUltimateCollider* col = dynamic_cast<BowUltimateCollider*>(obj);
			col->setPlayer(player);
			objectsList.push_back(obj);
		}
	}

	if (player->getSword()) {
		for (DrawableObject* obj : player->getSword()->getChainAttackList()) {
			PlayerAttackCollider* col = dynamic_cast<PlayerAttackCollider*>(obj);
			col->setPlayer(player);
			objectsList.push_back(obj);
		}
	}

	if (player->getShield()) {
		for (DrawableObject* obj : player->getShield()->getChainAttackList()) {
			PlayerAttackCollider* col = dynamic_cast<PlayerAttackCollider*>(obj);
			col->setPlayer(player);
			objectsList.push_back(obj);
		}
	}


	Ziz* ziz_ = new Ziz();
	objectsList.push_back(ziz_);
	ziz = ziz_;
	ziz->setLevel(this);
	ziz->setPlayer(player);
	ziz->setIdleState();


	/*Gust* gust_ = new Gust();
	objectsList.push_back(gust_);
	gust = gust_;
	gust->getTransform().setPosition(glm::vec3(0.0f, -2.0f, 0.0f));*/

	/*StormRise* stormRise_ = new StormRise();
	objectsList.push_back(stormRise_);
	stormRise = stormRise_;
	stormRise->getTransform().setPosition(glm::vec3(0.0f,-2.0f,0.0f));
	stormRise->setPlayer(player);*/


	/*SwoopWarning* warning = new SwoopWarning();
	objectsList.push_back(warning);*/

	SimpleObject* floor = new SimpleObject();
	floor->getTransform().setPosition(glm::vec3(0.0f, -3.5f, 0.0f));
	floor->getTransform().setScale(glm::vec3(18.0f, 2.0f, 0.0f));
	floor->addColliderComponent();
	floor->setName("Floor");
	floor->setDrawCollider(true);
	objectsList.push_back(floor);


	//cout << "Init Level" << endl;

	


}

void LevelBossTest::levelUpdate() {
	dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	timeK += dt;
	updateObjects(objectsList);

	tempx2 = tempx;
	tempx = ziz->getTransform().getPosition().y;
	if (tempx2 != tempx) {
		//cout << "Ziz X: " << ziz->getTransform().getPosition().x << endl;
	}
	//cout << "Ziz X: " << ziz->getTransform().getPosition().x << endl;
	/*float distance = abs(ziz->getTransform().getPosition().x - player->getTransform().getPosition().x);
	cout << "Distance: " << distance << endl;*/

	//cout << ziz->getCurrentHealth() << endl;

	if (ziz->getStateMachine()) {
		ziz->getStateMachine()->update(ziz, dt);
	}

	if (player->getStateMachine()) {
		player->getStateMachine()->update(player, dt);
	}
	


	for (DrawableObject* obj : objectsList) {
		
		Gust* gust = dynamic_cast<Gust*>(obj);
		if (gust) {
			gust->update(dt);
		}

		StormRise* stormRise = dynamic_cast<StormRise*>(obj);
		if (stormRise) {
			stormRise->update(dt);
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

		SwoopWarning* swoopWarning = dynamic_cast<SwoopWarning*>(obj);
		if (swoopWarning) {
			swoopWarning->update(dt);
		}

		BowUltimateCollider* attackCollider = dynamic_cast<BowUltimateCollider*>(obj);
		if (attackCollider) {
			attackCollider->update(dt);
		}
		

	}

	player->selfUpdate(dt);
	player->getSword()->update(dt, player);
	player->getBow()->update(dt, player);
	player->getShield()->update(dt, player);

	player->getAnimationComponent()->updateCurrentState(dt);

	handleObjectCollision(objectsList);

}

void LevelBossTest::levelDraw() {
	GameEngine::getInstance()->render(objectsList);
	//cout << "Draw Level" << endl;
}

void LevelBossTest::levelFree() {
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	//cout << "Free Level" << endl;
}

void LevelBossTest::levelUnload() {
	GameEngine::getInstance()->clearMesh();
	//cout << "Unload Level" << endl;
}

void LevelBossTest::handleKey(char key) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float speed = 20.0f;
	speed *= dt;

	bool playerIsMoving = false;

	//Jump -> higher priority

	if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
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
	case 'm':
		//cout << "M pressed" << endl;
		ziz->changePhase();
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
	case 'e': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_LEVEL1; ; break;
	case 'f': player->getBow()->setEnableDebug(); break;
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
	case 'l':
		cout << "L" << endl;
		/*cout << "Spawned Storm Rise" << endl;
		StormRise* stormRise_ = new StormRise();
		objectsList.push_back(stormRise_);
		stormRise = stormRise_;
		stormRise->getTransform().setPosition(glm::vec3(0.0f, -2.0f, 0.0f));
		stormRise->setPlayer(player);*/

		break;
	}


	/*if (!playerIsMoving) {
		player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
	}*/
}




void LevelBossTest::handleMouse(int type, int x, int y) {
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;

	GameEngine::getInstance()->getWindowWidth();
	GameEngine::getInstance()->getWindowHeight();

	//cout << "X : " << realX << " Y : " << realY << endl;

	//Check player weapon
	// assume type = bow first

	if (player->getWeaponType() == Bow_) {
		if (type == 0) {
			if (player->getBow()->getIsOverheat() == false) {
				if (player->getBow()->getRapidShotReady()) {
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

			if (player->getSword()->getInChainAttack()) {
				//input buffer
				player->getSword()->setInputBuffer(true);
				return;
			}

			switch (player->getSword()->getCurrentChainAttack()) {
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
			if (player->getSword()->getInChainAttack()) {
				return;
			}

			player->getStateMachine()->changeState(PlayerHeavySwordAttack::getInstance(), player);
		}

	}
	else if (player->getWeaponType() == Shield_) {
		if (type == 0) {
			//enter first attack of the chain

			if (player->getShield()->getInChainAttack()) {
				//input buffer
				player->getShield()->setInputBuffer(true);
				return;
			}

			switch (player->getShield()->getCurrentChainAttack()) {
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
			if (player->getShield()->getInChainAttack()) {
				return;
			}

			player->getStateMachine()->changeState(PlayerShieldGuard::getInstance(), player);
		}
		else if (type == 3) {

			if (player->getShield()->getIsBlocking()) {
				player->getStateMachine()->changeState(PlayerOffShield::getInstance(), player);
			}
		}
	}
}

void LevelBossTest::handleAnalogStick(int type, float amount) {
	float dt_ = GameEngine::getInstance()->getTime()->getDeltaTime();
	float speed = 20.0f;
	speed *= dt_;

	if (type == 0) {//x axis
		player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		if (amount < -0.05f) {
			player->setFacingRight(false);
			player->getTransform().translate(glm::vec3(-player->getMovementSpeed() * dt_, 0, 0));
		}
		else if (amount > 0.05f) {
			player->setFacingRight(true);
			player->getTransform().translate(glm::vec3(player->getMovementSpeed() * dt_, 0, 0));
		}
	}
}

void LevelBossTest::addObject(DrawableObject* obj) {
	objectsList.push_back(obj);
}