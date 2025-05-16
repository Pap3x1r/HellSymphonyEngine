
#include "GameEngine.h"

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine() {
	renderer = nullptr;
}

GameEngine * GameEngine::getInstance() {
	if (instance == nullptr) {
		instance = new GameEngine();
	}
	return instance;
}

GLRenderer * GameEngine::getRenderer() {
	return this->renderer;
}

GameStateController* GameEngine::getStateController() {
	return this->stateController;
}

Time* GameEngine::getTime() {
	return this->time;
}

AudioEngine* GameEngine::getAudio() {
	return this->audio;
}

InputManager* GameEngine::getInputHandler() {
	return inputHandler;
}
void GameEngine::init(int width, int height) {
	winWidth = width;
	winHeight = height;

	renderer = new GLRenderer(width, height);
	renderer->initGL("../Resource/Shader/vertext.shd", "../Resource/Shader/fragment.shd");
	setDrawArea(-8, 8, -4.5, 4.5);
	setBackgroundColor(95.0f / 255, 110.0f / 255, 133.0f / 255);

	texturePaths = { //vector holding paths (might create something that automatically load files into map for easier use)
		//Sword
		"../Resource/Texture/Dante/DanteSword/dante_idle_sword.png", //path
		"../Resource/Texture/Dante/DanteSword/dante_walking_sword.png",
		"../Resource/Texture/Dante/DanteSword/dante_jumping_sword.png",
		"../Resource/Texture/Dante/DanteSword/dante_dash_sword.png",
		"../Resource/Texture/Dante/DanteSword/dante_lightAttack1_sword.png",
		"../Resource/Texture/Dante/DanteSword/dante_lightAttack2_sword.png",
		"../Resource/Texture/Dante/DanteSword/dante_lightAttack3_sword.png",
		"../Resource/Texture/Dante/DanteSword/dante_heavyAttack_sword.png",
		"../Resource/Texture/Dante/DanteSword/dante_smallUlt_sword.png",
		//Shield
		"../Resource/Texture/Dante/DanteShield/dante_idle_shield.png", //path
		"../Resource/Texture/Dante/DanteShield/dante_walking_shield.png",
		"../Resource/Texture/Dante/DanteShield/dante_jumping_shield.png",
		"../Resource/Texture/Dante/DanteShield/dante_falling_shield.png",
		"../Resource/Texture/Dante/DanteShield/dante_dash_shield.png",
		"../Resource/Texture/Dante/DanteShield/dante_lightAttack1_shield.png",
		"../Resource/Texture/Dante/DanteShield/dante_lightAttack2_shield.png",
		"../Resource/Texture/Dante/DanteShield/dante_holding_shield.png",
		"../Resource/Texture/Dante/DanteShield/dante_off_shield.png",
		"../Resource/Texture/Dante/DanteShield/dante_smallUlt_shield.png",
		"../Resource/Texture/Dante/DanteShield/dante_bigUlt_shield.png",
		//Bow
		"../Resource/Texture/Dante/DanteBow/dante_idle_bow.png", //path
		"../Resource/Texture/Dante/DanteBow/dante_walking_bow.png",
		"../Resource/Texture/Dante/DanteBow/dante_jumping_bow.png",
		"../Resource/Texture/Dante/DanteBow/dante_falling_bow.png",
		"../Resource/Texture/Dante/DanteBow/dante_dash_bow.png",
		"../Resource/Texture/Dante/DanteBow/dante_lightAttack_bow.png",
		"../Resource/Texture/Dante/DanteBow/dante_heavyAttack_bow.png",
		"../Resource/Texture/Dante/DanteBow/dante_smallUlt_bow.png",
		"../Resource/Texture/Dante/DanteBow/dante_bigUlt_bow.png",
	};

	GameEngine::getInstance()->getRenderer()->preloadTextures(texturePaths); //preload all paths

	stateController = new GameStateController();
	stateController->init(GameState::GS_LEVEL1);

	time = new Time();
	inputHandler = new InputManager();  
	TTF_Init();
}

void GameEngine::render(list<DrawableObject*> renderObjects) {
	this->getRenderer()->render(renderObjects);
}

void GameEngine::setDrawArea(float left, float right, float bottom, float top) {
	renderer->setOrthoProjection(left, right, bottom, top);
}

//void GameEngine::setBackgroundColor(float r, float g, float b) {
//	renderer->setClearColor(1.0f, 1.0f, 200.0f / 255);
//}

void GameEngine::setBackgroundColor(float r, float g, float b) {
	renderer->setClearColor(r, g, b);
}

void GameEngine::addMesh(string name, MeshVbo* mesh) {
	renderer->addMesh(name, mesh);
}

void GameEngine::clearMesh() {
	renderer->clearMesh();
}

int GameEngine::getWindowWidth() {
	return winWidth;
}

int GameEngine::getWindowHeight() {
	return winHeight;
}

void GameEngine::setWindowWidth(int w) {
	winWidth = w;
}
void GameEngine::setWindowHeight(int h) {
	winHeight = h;
}

void GameEngine::freezeGameForSecond(float duration) {
	while (duration > 0.0f) {
		time->updateTick(SDL_GetTicks());
		duration -= time->getDeltaTimeRealTime();
	}
}