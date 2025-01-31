#include "LevelAnimTest.h"


void LevelAnimTest::levelLoad() {
	SquareMeshVbo * square = new SquareMeshVbo();
	square->loadData();
	GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

	//cout << "Load Level" << endl;
}

void LevelAnimTest::levelInit() {
	TexturedObject * obj = new TexturedObject();
	obj->setTexture("../Resource/Texture/dog.png");
	obj->getTransform().setScale(glm::vec3(1.5f, -1.5f,0));
	obj->isAnimation(4, 4);
	obj->setFrame(0, 0);
	objectsList.push_back(obj);

	player = obj;
	player->addColliderComponent();

	//cout << "Init Level" << endl;
}

void LevelAnimTest::levelUpdate() {
	//cout << "Update Level" << endl;
	if (d > 5) {
		player->setFrame(row, col);
		row++;
		if (row > 3) {
			row = 0;
			col++;
		}
		if (col > 3) {
			col = 0;
		}
		d = 0;
	}
	d++;
}

void LevelAnimTest::levelDraw() {
	GameEngine::getInstance()->render(objectsList);
	player->drawCollider();
	//cout << "Draw Level" << endl;
}

void LevelAnimTest::levelFree() {
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	//cout << "Free Level" << endl;
}

void LevelAnimTest::levelUnload() {
	GameEngine::getInstance()->clearMesh();
	//cout << "Unload Level" << endl;
}

void LevelAnimTest::handleKey(char key) {

	switch (key) {
		case 'w': player->getTransform().translate(glm::vec3(0, 0.3, 0)); break;
		case 's': player->getTransform().translate(glm::vec3(0, -0.3, 0)); break;
		case 'a': player->getTransform().translate(glm::vec3(-0.3, 0, 0)); break;
		case 'd': player->getTransform().translate(glm::vec3(0.3, 0, 0)); break;
		case 'q': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_QUIT; ; break;
		case 'r': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART; ; break;
		case 'e': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_LEVEL2; ; break;
	}
}

void LevelAnimTest::handleMouse(int type, int x, int y) {
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;

	GameEngine::getInstance()->getWindowWidth();
	GameEngine::getInstance()->getWindowHeight();

	cout << "X : " << realX << " Y : " << realY << endl;

	player->getTransform().setPosition(glm::vec3(realX, realY, 0));
}


