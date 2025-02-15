#include "LevelBossTest.h"
#include "CollisionHandler.h"


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

	Ziz* ziz_ = new Ziz();
	objectsList.push_back(ziz_);
	ziz = ziz_;
	ziz->setLevel(this);
	ziz->getTransform().setPosition(glm::vec3(5.0f,2.0f,0.0f));

	Player* player_ = new Player(10);
	objectsList.push_back(player_);
	player = player_;
	player->setLevel(this);

	SimpleObject* floor = new SimpleObject();
	floor->getTransform().setPosition(glm::vec3(0.0f, -3.5f, 0.0f));
	floor->getTransform().setScale(glm::vec3(18.0f, 2.0f, 0.0f));
	floor->addColliderComponent();
	floor->setDrawCollider(true);
	objectsList.push_back(floor);

	//cout << "Init Level" << endl;
}

void LevelBossTest::levelUpdate() {
	dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	timeK += dt;
	updateObjects(objectsList);

	//ziz->getStateMachine()->update(ziz, dt);

	for (DrawableObject* obj : objectsList) {


	}

	

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

	switch (key) {

		case 'q': 
			GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_QUIT; 
			break;

		case 'r':
			GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART;
			break;

		case 'e':
			GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_LEVEL1;
			break;

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

		default:
			break;

	}
}

void LevelBossTest::handleMouse(int type, int x, int y) {
	//float realX, realY;

	//// Calculate Real X Y 
	//realX = x;
	//realY = y;

	//GameEngine::getInstance()->getWindowWidth();
	//GameEngine::getInstance()->getWindowHeight();

	////cout << "X : " << realX << " Y : " << realY << endl;

	////Check player weapon
	//// assume type = bow first
	//if (type == 0) {
	//	if (bow->getIsOverheat() == false) {
	//		if (bow->getRapidShotReady()) {
	//			/*DrawableObject* newArrow = bow->arrowShot(10, player, 25);
	//			objectsList.push_back(newArrow);*/
	//			player->getStateMachine()->changeState(PlayerLightBowAttack::getInstance(), player);
	//		}
	//	}
	//}
	//else {
	//	DrawableObject* newArrow = bow->arrowShot(100, player, 50);
	//	objectsList.push_back(newArrow);
	//}


	//player->getTransform().setPosition(glm::vec3(realX, realY, 0));
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