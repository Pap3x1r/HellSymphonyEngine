#include "LevelPrototype.h"
#include "CollisionHandler.h"

#include <fstream>
static bool qteStarted = false;

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
	Player* player_ = loadPlayerData("../Resource/Saves/PlayerData/playerData.txt");
	//Player* player_ = new Player(100, 0, 3);
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

	SimpleObject* witherHealthBar_ = new SimpleObject();
	witherHealthBar_->setColor(106.0f / 255.0f, 109.0f / 255.0f, 115.0f / 255.0f);
	witherHealthBar_->getTransform().setScale(glm::vec3(4.5f, 0.45f, 0.0f));
	witherHealthBar_->getTransform().setPosition(glm::vec3(-4.0f, -4.0f, 0.0f));
	objectsList.push_back(witherHealthBar_);
	witherHealthBar = witherHealthBar_;

	SimpleObject* healthBar = new SimpleObject();
	healthBar->setColor(0.0f, 1.0f, 0.0f);
	healthBar->getTransform().setScale(glm::vec3(4.5f, 0.45f, 0.0f));
	healthBar->getTransform().setPosition(glm::vec3(-4.0f, -4.0f, 0.0f));
	objectsList.push_back(healthBar);
	playerHealthBar = healthBar;

	SimpleObject* ultimateBar = new SimpleObject();
	ultimateBar->setColor(235.0f / 255.0f, 168.0f / 255.0f, 52.0f / 255.0f);
	ultimateBar->getTransform().setScale(glm::vec3(2.5f, 0.18f, 0.0f));
	ultimateBar->getTransform().setPosition(glm::vec3(-4.0f, -3.65f, 0.0f));
	objectsList.push_back(ultimateBar);
	playerUltimateBar = ultimateBar;

	//cout << "Init Level" << endl;
}

void LevelPrototype::levelUpdate() {
	dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	timeK += dt;
	player->getStateMachine()->update(player, dt);

	updateObjects(objectsList);

	if (qteStarted) {
		qteStarted = false;
		QTEManager* qteManager = QTEManager::getInstance();
		qteManager->startQTE({ 'S', 'P' }, 999999999.0f);
	}

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

	float healthOriginalWidth = 4.5f;
	float healthBaseX = -5.7f;

	//Health Bar
	float healthPercentage = player->getHealth()->getCurrentHP() / player->getHealth()->getMaxHP();
	healthPercentage = glm::clamp(healthPercentage, 0.0f, 1.0f);

	float healthWidth = healthPercentage * healthOriginalWidth;

	float healthX = healthBaseX - (healthOriginalWidth * 0.5f) + (healthWidth * 0.5f);

	playerHealthBar->getTransform().setScale(glm::vec3(healthWidth, playerHealthBar->getTransform().getScale().y, playerHealthBar->getTransform().getScale().z));
	playerHealthBar->getTransform().setPosition(glm::vec3(healthX, -4.0f, 0.0f));

	//Wither Health Bar
	float totalHealthPercentage = (player->getHealth()->getCurrentHP() + player->getHealth()->getWitherHP()) / player->getHealth()->getMaxHP();
	totalHealthPercentage = glm::clamp(totalHealthPercentage, 0.0f, 1.0f);

	float witherWidth = totalHealthPercentage * healthOriginalWidth;

	float witherX = healthBaseX - (healthOriginalWidth * 0.5f) + (witherWidth * 0.5f);

	witherHealthBar->getTransform().setScale(glm::vec3(witherWidth, witherHealthBar->getTransform().getScale().y, witherHealthBar->getTransform().getScale().z));
	witherHealthBar->getTransform().setPosition(glm::vec3(witherX, -4.0f, 0.0f));

	//Ultimate Bar
	float ultimateOriginalWidth = 2.5f;
	float ultimateBaseX = -6.7f;

	float ultimatePercentage = (player->getUltimateSlot() * 100.0f + player->getUltimateGauge()) / (player->getUltimateSlotMax() * 100.0f);
	ultimatePercentage = glm::clamp(ultimatePercentage, 0.0f, 1.0f);

	float ultimateWidth = ultimatePercentage * ultimateOriginalWidth;

	float ultimateX = ultimateBaseX - (ultimateOriginalWidth * 0.5f) + (ultimateWidth * 0.5f);

	playerUltimateBar->getTransform().setScale(glm::vec3(ultimateWidth, playerUltimateBar->getTransform().getScale().y, playerUltimateBar->getTransform().getScale().z));
	playerUltimateBar->getTransform().setPosition(glm::vec3(ultimateX, -3.65f, 0.0f));

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

	QTEManager* qteManager = QTEManager::getInstance();
	if (key != 'I') {
		qteManager->handleInput(key);
	}
	//Jump -> higher priority

	if (sword->getInChainAttack() || shield->getInChainAttack() || shield->getIsHolding() || bow->getIsShooting() || player->getIsDashing()) { //Prevent returning back to idle
		if (!player->getIsDashing()) {
			player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
		}
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
	case 'r': 
		savePlayerData(getPlayer(), "../Resource/Saves/PlayerData/playerData.txt");
		GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART;
		break;
	case 'e': 
		savePlayerData(getPlayer(), "../Resource/Saves/PlayerData/playerData.txt");
		GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_MAINMENU;
		//qteStarted = true;
		break;
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

	if (player->getIsDashing() || !player->getIsGrounded()) { //Prevent returning
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

Player* LevelPrototype::getPlayer() const {
	return player;
}

void LevelPrototype::savePlayerData(const Player* player, const std::string& filename) {
	ofstream outFile(filename);
	if (!outFile) {
		cerr << "Error opening file for writing!" << endl;
		return;
	}

	// Save player data with descriptions and line breaks
	outFile << "Player Health: " << getPlayer()->getHealth()->getCurrentHP() << endl;
	outFile << "Player Wither Health: " << getPlayer()->getHealth()->getWitherHP() << endl;
	outFile << "Player Lives: " << getPlayer()->getLives() << endl;

	outFile.close();
}

Player* LevelPrototype::loadPlayerData(const string& filepath) {
	ifstream inFile(filepath);
	if (!inFile) {
		cerr << "Error opening file for reading! Using default values.\n";
		return new Player(100, 0, 3);
	}

	string line;

	float hp = 100.0f;
	float wither = 0.0f;
	int lives = 3;

	auto extractValue = [&inFile](const string& label, auto& value) {
		string line;
		if (getline(inFile, line)) {
			size_t pos = line.find(label);
			if (pos != string::npos) {
				try {
					value = stof(line.substr(pos + label.length()));  // Convert to float or int
				}
				catch (...) {
					cerr << "Error reading " << label << endl;
				}
			}
		}
	};

	extractValue("Player Health:", hp);
	extractValue("Player Wither Health:", wither);
	extractValue("Player Lives:", lives);


	inFile.close();
	cout << "Data loaded from text file.\n";

	cout << "Player health: " << hp << endl;
	cout << "Player wither health: " << wither << endl;
	cout << "Player lives: " << lives << endl;

	Player* player_ = new Player(hp, wither, lives);
	/*player_->getHealth()->setHP(hp);
	player_->getHealth()->setWitherHP(wither);
	player_->setLives(lives);*/

	return player_;
}