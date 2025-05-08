#include "LevelMainMenu.h"
#include "CollisionHandler.h"
#include "GameEngine.h"
#include "GLRenderer.h" 
#include <iostream>
#include <random>
using namespace std;




void LevelMainMenu::levelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->loadData();
	GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

	SquareBorderMesh* border = new SquareBorderMesh();
	border->loadData();
	GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);

	//cout << "Load Level" << endl;
}

void LevelMainMenu::levelInit() {

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Play Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* playText = new UIText("Play Text");
	SDL_Color playTextColor = { 255,255,255,255 };
	playText->loadText("Hello", playTextColor, 100);
	playText->setText("Play");
	playText->setAlpha(1.0f);
	playText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	playText->getTransform().setPosition(glm::vec3(0.3f, 0.0f, 0.0f));
	playText->addColliderComponent();
	/*playText->setDrawCollider(true);
	playText->setCanDrawColliderNew(true);*/
	objectsList.push_back(playText);

	UIButton* playButton = new UIButton("Play Button");
	//playButton->setTexture("../Resource/Texture/UI/UIButton.png");
	playButton->getTransform().setPosition(glm::vec3(0.0f, 0.3f, 0.0f));
	playButton->getTransform().setScale(glm::vec3(1.1f, 0.45f, 0.0f));
	playButton->addColliderComponent();
	playButton->setDrawCollider(true);
	playButton->setCanDrawColliderNew(true);
	playButton->setDraw(false);
	playButton->setLabel(playText); // Link playText
	objectsList.push_back(playButton);
	buttonsList.push_back(playButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Continue Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* continueText = new UIText("Continue Text");
	SDL_Color continueTextColor = { 255,255,255,255 };
	continueText->loadText("Continue", continueTextColor, 100);
	continueText->setText("Continue");
	continueText->setAlpha(1.0f);
	continueText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	continueText->getTransform().setPosition(glm::vec3(0.38f, -0.5f, 0.0f));
	continueText->getTransform().setScale(glm::vec3(3.0f, 1.31f, 0.0f));
	continueText->addColliderComponent();
	/*continueText->setDrawCollider(true);
	continueText->setCanDrawColliderNew(true);*/
	objectsList.push_back(continueText);

	UIButton* continueButton = new UIButton("Continue Button");
	//continueButton->setTexture("../Resource/Texture/UI/UIButton.png");
	continueButton->getTransform().setPosition(glm::vec3(0.0f, -0.23f, 0.0f));
	continueButton->getTransform().setScale(glm::vec3(2.2f, 0.45f, 0.0f));
	continueButton->addColliderComponent();
	continueButton->setDrawCollider(true);
	continueButton->setCanDrawColliderNew(true);
	continueButton->setDraw(false);
	continueButton->setLabel(continueText); // Link continueText
	objectsList.push_back(continueButton);
	buttonsList.push_back(continueButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Settings Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* settingsText = new UIText("Settings Text");
	SDL_Color settingsTextColor = { 255,255,255,255 };
	settingsText->loadText("Settings", settingsTextColor, 100);
	settingsText->setText("Settings");
	settingsText->setAlpha(1.0f);
	settingsText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	settingsText->getTransform().setPosition(glm::vec3(0.61f, -1.05f, 0.0f));
	settingsText->getTransform().setScale(glm::vec3(3.02f, 1.31f, 0.0f));
	settingsText->addColliderComponent();
	/*settingsText->setDrawCollider(true);
	settingsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(settingsText);

	UIButton* settingsButton = new UIButton("Settings Button");
	//settingsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	settingsButton->getTransform().setPosition(glm::vec3(0.0f, -0.76f, 0.0f));
	settingsButton->getTransform().setScale(glm::vec3(1.8f, 0.45f, 0.0f));
	settingsButton->addColliderComponent();
	settingsButton->setDrawCollider(true);
	settingsButton->setCanDrawColliderNew(true);
	settingsButton->setDraw(false);
	settingsButton->setLabel(settingsText); // Link playText
	objectsList.push_back(settingsButton);
	buttonsList.push_back(settingsButton);

	//GameEngine::getInstance()->freezeGameForSecond(1.6f);
}

void LevelMainMenu::levelUpdate() {
	dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	timeK += dt;
	updateObjects(objectsList);

	ImGui::SetWindowSize(ImVec2(400, 300));
	ImGui::Begin("Debug Panel");

	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	for (UIButton* button : buttonsList) {
		button->isHovered(mouseX, mouseY);
	}



	for (DrawableObject* obj : objectsList) {
		UIText* text = dynamic_cast<UIText*>(obj);
		if (text) {
			text->update(dt);
		}

		UIButton* button = dynamic_cast<UIButton*>(obj);
		if (button) {
			button->update(dt);
		}
	}



	handleObjectCollision(objectsList);

	ImGui::End();
}

void LevelMainMenu::levelDraw() {
	GameEngine::getInstance()->render(objectsList);
}

void LevelMainMenu::levelFree() {
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}

	for (UIButton*& button : buttonsList) {
		button = nullptr;
	}
	objectsList.clear();
	buttonsList.clear();
}

void LevelMainMenu::levelUnload() {
	GameEngine::getInstance()->clearMesh();
}

void LevelMainMenu::isReceivingNoInputs() {
	
}

void LevelMainMenu::handleKey(char key) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	
}

void LevelMainMenu::handleControllerButton(SDL_GameControllerButton button) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	
}


void LevelMainMenu::handleMouse(int type, int x, int y) {
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;

	GameEngine::getInstance()->getWindowWidth();
	GameEngine::getInstance()->getWindowHeight();

	//cout << "X : " << realX << " Y : " << realY << endl;

	for (UIButton* button : buttonsList) {
		if (button->getMouseOver()) {
			if (type == 0) {
				GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART;
			}
		}
	}

}

void LevelMainMenu::handleAnalogStick(int type, char key) {
	float dt_ = GameEngine::getInstance()->getTime()->getDeltaTime();


}

void LevelMainMenu::addObject(DrawableObject* obj) {
	objectsList.push_back(obj);
}

