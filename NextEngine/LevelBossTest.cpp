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

		default:
			break;

	}
}