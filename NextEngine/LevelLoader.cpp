#include "LevelLoader.h"
#include "CollisionHandler.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void LevelLoader::levelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->loadData();
	GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

	SquareBorderMesh* border = new SquareBorderMesh();
	border->loadData();
	GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);

	//loadingThread = thread([this]() {
	//	GLRenderer* renderer = GameEngine::getInstance()->getRenderer();
	//	
	//	if (renderer) {
	//		for (const string& dir : textureDirsToLoad) {
	//			renderer->loadTextureFromDir(dir);
	//		}
	//	}

	//	texturesLoaded = true; // Mark loading complete
	//	std::cout << "Current cache size: " << GameEngine::getInstance()->getRenderer()->getTextureCache().size() << std::endl;
	//	});

	//loadingThread.detach();

	gatherTexturesFromDirs(textureDirsToLoad);
}

void LevelLoader::levelInit() {

	TexturedObject* background = new TexturedObject("Background");
	background->setTexture("../Resource/Texture/LoadingScreenBG.png");
	background->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	objectsList.push_back(background);

	TexturedObject* danteWalking = new TexturedObject("Dante");
	danteWalking->initAnimation(0, 0);
	danteWalking->getAnimationComponent()->addState("walkingSword", 0, 8);
	danteWalking->setTexture("../Resource/Texture/Dante/DanteSword/dante_walking_sword.png", 1, 8, 0); //set new texture ("path", row, column)
	danteWalking->getAnimationComponent()->setState("walkingSword"); //set state
	danteWalking->getTransform().setScale(glm::vec3(3.25f, 3.25f, 1.0f));
	danteWalking->getTransform().setPosition(glm::vec3(-6.35f, -2.45f, 1.0f));
	objectsList.push_back(danteWalking);

	TexturedObject* blackFade_ = new TexturedObject("Black Fade");
	blackFade_->setTexture("../Resource/Texture/blackFade.png");
	blackFade_->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	objectsList.push_back(blackFade_);
	blackFade = blackFade_;
	blackFade->setAlpha(1.0f);
	firstStart = true;

	currentTextureIndex = 0;
	//GameEngine::getInstance()->freezeGameForSecond(1.6f);
}

void LevelLoader::levelUpdate() {
	dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float playerDT = dt * playerTimeScale;
	timeK += dt;
	updateObjects(objectsList);

	if (firstStart) {
		if (blackFade) {
			blackFadeTransitionTime += dt;
			float t = blackFadeTransitionTime / blackFadeTransitionDuration;
			bool finishBlackFade = false;
			if (t >= 1.0f) {
				t = 1.0f;
				finishBlackFade = true;
			}

			blackFade->setAlpha(1.0f - t);

			if (finishBlackFade) {
				firstStart = false;
				blackFade->setAlpha(0.0f);
			}
		}
	}

	for (DrawableObject* obj : objectsList) {

		TexturedObject* texturedObj = dynamic_cast<TexturedObject*>(obj);
		if (texturedObj) {
			if (texturedObj->getAnimationComponent()) {
				texturedObj->getAnimationComponent()->updateCurrentState(playerDT);
			}
		}

	}

	loadOneTexturePerFrame();

	handleObjectCollision(objectsList);
}

void LevelLoader::levelDraw() {
	GameEngine::getInstance()->render(objectsList);
	//cout << "Draw Level" << endl;
}

void LevelLoader::levelFree() {
	//savePlayerData(player, "../Resource/Saves/PlayerData/playerData.txt");

	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	//cout << "Free Level" << endl;
}

void LevelLoader::levelUnload() {
	GameEngine::getInstance()->clearMesh();
	//cout << "Unload Level" << endl;
}

void LevelLoader::handleKey(char key) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float speed = 20.0f;
	speed *= dt;

	bool playerIsMoving = false;

	//Jump -> higher priority

	switch (key) {
	case 'w':

		break;
	case 's':

	case 'a':

		break;
	case 'd':

		break;
	case 'm':

		break;
	case 'q':

		break;
	case 'r': 
		GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART; 
		break;
	case 'h':

		break;
	case 'j':

		break;
	case 'g':

		break;
	case 'I': //No Movement Input -> Idle


		break;
	case 'S': //Spacebar -> Jump

		break;
	case 'P': // dash

		break;
	case 't':

		break;

	case 'l':

		break;
	}
}

void LevelLoader::handleControllerButton(SDL_GameControllerButton button) {

}


void LevelLoader::handleMouse(int type, int x, int y) {

	
}

void LevelLoader::handleAnalogStick(int type, char key) {

	if (type == 0) {//x axis
		switch (key) {
		case 'l':

			break;
		case  'r':

			break;

		}
	}
}

void LevelLoader::addObject(DrawableObject* obj) {
	objectsList.push_back(obj);
}

void LevelLoader::configure(const std::vector<std::string>& dirs, GameState nextState_) {
	textureDirsToLoad = dirs;
	nextState = nextState_;
	texturesLoaded = false;
}

void LevelLoader::gatherTexturesFromDirs(const vector<string>& dirs) {
	texturePathsToLoad.clear();
	for (const string& dir : dirs) {
		for (const auto& paths : fs::recursive_directory_iterator(dir)) {
			if (paths.is_regular_file() && paths.path().extension() == ".png") {
				texturePathsToLoad.push_back(paths.path().string());
			}
		}
	}
}

void LevelLoader::loadOneTexturePerFrame() {
	if (!texturesLoaded && currentTextureIndex < texturePathsToLoad.size()) {
		GameEngine::getInstance()->getRenderer()->findTexture(texturePathsToLoad[currentTextureIndex]);
		currentTextureIndex++;
	}

	if (!texturesLoaded && currentTextureIndex >= texturePathsToLoad.size()) {
		texturesLoaded = true;
		std::cout << "All textures loaded.\n";
		GameEngine::getInstance()->getStateController()->gameStateNext = nextState;
	}
}