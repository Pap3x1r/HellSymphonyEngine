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

	Sword* sword_ = new Sword();
	if (sword_) {
		for (DrawableObject* obj : sword_->getChainAttackList()) {
			objectsList.push_back(obj);
		}
	}
	sword = sword_;

	Player* player_ = new Player(10);
	objectsList.push_back(player_);
	player = player_;
	player->setLevel(this);

	bow = player->getBow();

	Enemy* enemy_ = new Enemy(10);
	objectsList.push_back(enemy_);
	objectsList.push_back(enemy_->getEnemyAttackCollider());
	enemy = enemy_;

	SimpleObject* floor = new SimpleObject();
	floor->getTransform().setPosition(glm::vec3(0.0f, -3.5f, 0.0f));
	floor->getTransform().setScale(glm::vec3(18.0f, 2.0f, 0.0f));
	floor->addColliderComponent();
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
	}
		
	sword->update(dt, player);
	bow->update(dt, player);

	//for (DrawableObject* obj : objectsList) { //Update enemy object
	//	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	//	if (enemy && enemy->getEnemyAttackCollider()) {
	//		// Update attackCollider to follow enemy
	//		enemy->getEnemyAttackCollider()->getTransform().setPosition(enemy->getTransform().getPosition());
	//	}
	//}



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

	switch (key) {
	case 'w':
		player->getTransform().translate(glm::vec3(0, player->getMovementSpeed() * dt, 0));
		player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		playerIsMoving = true;
		//player->getAnimationComponent()->setState("up");
		break;
	case 's': 
		player->getTransform().translate(glm::vec3(0, -player->getMovementSpeed() * dt, 0));
		player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		playerIsMoving = true;
		//player->getAnimationComponent()->setState("down");
		break;
	case 'a': 
		player->getTransform().translate(glm::vec3(-player->getMovementSpeed() * dt, 0, 0));
		player->setFacingRight(false);
		player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		playerIsMoving = true;
		//player->getAnimationComponent()->setState("left");
		break;
	case 'd': 
		player->getTransform().translate(glm::vec3(player->getMovementSpeed() * dt, 0, 0));
		player->setFacingRight(true);
		player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		playerIsMoving = true;
		//player->getAnimationComponent()->setState("right");
		break;
	case 'q': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_QUIT; ; break;
	case 'r': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART; ; break;
	case 'e': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_LEVEL2; ; break;
	case 'f': bow->setEnableDebug();
	}

	if (!playerIsMoving) {
		player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
	}
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
	if (type == 0) {
		if (bow->getIsOverheat() == false) {
			if (bow->getRapidShotReady()) {
				/*DrawableObject* newArrow = bow->arrowShot(10, player, 25);
				objectsList.push_back(newArrow);*/
				player->getStateMachine()->changeState(PlayerLightBowAttack::getInstance(), player);
			}
		}
	}
	else {
		DrawableObject* newArrow = bow->arrowShot(100, player, 50);
		objectsList.push_back(newArrow);
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
