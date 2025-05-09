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

	TexturedObject* background = new TexturedObject();
	background->setTexture("../Resource/Texture/newMainMenuBG.png");
	background->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	objectsList.push_back(background);

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
	continueText->getTransform().setPosition(glm::vec3(0.35f, 0.0f - 0.6f, 0.0f));
	continueText->getTransform().setScale(glm::vec3(2.7f, 1.31f, 0.0f));
	continueText->addColliderComponent();
	continueText->setMenuState(MenuState::MAIN);
	/*continueText->setDrawCollider(true);
	continueText->setCanDrawColliderNew(true);*/
	objectsList.push_back(continueText);

	UIButton* continueButton = new UIButton("Continue Button");
	//continueButton->setTexture("../Resource/Texture/UI/UIButton.png");
	continueButton->getTransform().setPosition(glm::vec3(0.0f, 0.3f - 0.6f, 0.0f));
	continueButton->getTransform().setScale(glm::vec3(2.05f, 0.45f, 0.0f));
	continueButton->addColliderComponent();
	continueButton->setDrawCollider(true);
	continueButton->setCanDrawColliderNew(true);
	continueButton->setDraw(false);
	continueButton->setLabel(continueText); // Link continueText
	continueButton->setMenuState(MenuState::MAIN);
	objectsList.push_back(continueButton);
	buttonsList.push_back(continueButton);

	mainButtons.push_back(continueButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										New Game Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* playText = new UIText("New Game Text");
	SDL_Color playTextColor = { 255,255,255,255 };
	playText->loadText("New Game", playTextColor, 100);
	playText->setText("New Game");
	playText->setAlpha(1.0f);
	playText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	playText->getTransform().setPosition(glm::vec3(0.2f, -0.525f - 0.7f, 0.0f));
	playText->getTransform().setScale(glm::vec3(2.7f, 1.31f, 0.0f));
	playText->addColliderComponent();
	playText->setMenuState(MenuState::MAIN);
	/*playText->setDrawCollider(true);
	playText->setCanDrawColliderNew(true);*/
	objectsList.push_back(playText);

	UIButton* playButton = new UIButton("New Game Button");
	//playButton->setTexture("../Resource/Texture/UI/UIButton.png");
	playButton->getTransform().setPosition(glm::vec3(0.0f, -0.23f - 0.7f, 0.0f));
	playButton->getTransform().setScale(glm::vec3(2.35f, 0.45f, 0.0f));
	playButton->addColliderComponent();
	playButton->setDrawCollider(true);
	playButton->setCanDrawColliderNew(true);
	playButton->setDraw(false);
	playButton->setLabel(playText); // Link playText
	playButton->setMenuState(MenuState::MAIN);
	playButton->setFunction([this]() {
		toBoss();
	});

	objectsList.push_back(playButton);
	buttonsList.push_back(playButton);

	mainButtons.push_back(playButton);

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
	settingsText->getTransform().setPosition(glm::vec3(0.62f, -1.05f - 0.8f, 0.0f));
	settingsText->getTransform().setScale(glm::vec3(3.0f, 1.31f, 0.0f));
	settingsText->addColliderComponent();
	settingsText->setMenuState(MenuState::MAIN);
	/*settingsText->setDrawCollider(true);
	settingsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(settingsText);

	UIButton* settingsButton = new UIButton("Settings Button");
	//settingsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	settingsButton->getTransform().setPosition(glm::vec3(0.0f, -0.76f - 0.8f, 0.0f));
	settingsButton->getTransform().setScale(glm::vec3(1.8f, 0.45f, 0.0f));
	settingsButton->addColliderComponent();
	settingsButton->setDrawCollider(true);
	settingsButton->setCanDrawColliderNew(true);
	settingsButton->setDraw(false);
	settingsButton->setLabel(settingsText); // Link playText
	settingsButton->setMenuState(MenuState::MAIN);
	objectsList.push_back(settingsButton);
	buttonsList.push_back(settingsButton);

	mainButtons.push_back(settingsButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Credits Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* creditsText = new UIText("Credits Text");
	SDL_Color creditsTextColor = { 255,255,255,255 };
	creditsText->loadText("Credits", creditsTextColor, 100);
	creditsText->setText("Credits");
	creditsText->setAlpha(1.0f);
	creditsText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	creditsText->getTransform().setPosition(glm::vec3(0.6f, -1.58f - 0.9f, 0.0f));
	creditsText->getTransform().setScale(glm::vec3(2.7f, 1.31f, 0.0f));
	creditsText->addColliderComponent();
	creditsText->setMenuState(MenuState::MAIN);
	/*creditsText->setDrawCollider(true);
	creditsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(creditsText);

	UIButton* creditsButton = new UIButton("Credits Button");
	//creditsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	creditsButton->getTransform().setPosition(glm::vec3(0.0f, -1.29f - 0.9f, 0.0f));
	creditsButton->getTransform().setScale(glm::vec3(1.5f, 0.45f, 0.0f));
	creditsButton->addColliderComponent();
	creditsButton->setDrawCollider(true);
	creditsButton->setCanDrawColliderNew(true);
	creditsButton->setDraw(false);
	creditsButton->setLabel(creditsText); // Link playText
	creditsButton->setMenuState(MenuState::MAIN);
	objectsList.push_back(creditsButton);
	buttonsList.push_back(creditsButton);

	mainButtons.push_back(creditsButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Quit Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* quitText = new UIText("Quit Text");
	SDL_Color quitTextColor = { 255,255,255,255 };
	quitText->loadText("Quit", quitTextColor, 100);
	quitText->setText("Quit");
	quitText->setAlpha(1.0f);
	quitText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	quitText->getTransform().setPosition(glm::vec3(0.18f, -2.1f - 1.0f, 0.0f));
	quitText->getTransform().setScale(glm::vec3(1.4f, 1.31f, 0.0f));
	quitText->addColliderComponent();
	quitText->setMenuState(MenuState::MAIN);
	/*quitText->setDrawCollider(true);
	quitText->setCanDrawColliderNew(true);*/
	objectsList.push_back(quitText);

	UIButton* quitButton = new UIButton("Quit Button");
	//creditsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	quitButton->getTransform().setPosition(glm::vec3(0.0f, -1.82f - 1.0f, 0.0f));
	quitButton->getTransform().setScale(glm::vec3(1.1f, 0.45f, 0.0f));
	quitButton->addColliderComponent();
	quitButton->setDrawCollider(true);
	quitButton->setCanDrawColliderNew(true);
	quitButton->setDraw(false);
	quitButton->setLabel(quitText); // Link playText
	quitButton->setMenuState(MenuState::MAIN);
	objectsList.push_back(quitButton);
	buttonsList.push_back(quitButton);

	mainButtons.push_back(quitButton);

	//GameEngine::getInstance()->freezeGameForSecond(1.6f);
}

void LevelMainMenu::levelUpdate() {
	dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	timeK += dt;
	updateObjects(objectsList);

	ImGui::SetWindowSize(ImVec2(400, 300));
	ImGui::Begin("Debug Panel");


	bool anyButtonHovered = false;
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	int index = 0; 
	for (auto it = buttonsList.begin(); it != buttonsList.end(); ++it, ++index) {
		UIButton* button = *it;
		bool isHovered = button->isHovered(mouseX, mouseY);

		if (selectedIndex != index) {
			button->setMouseOver(isHovered);
		}

		if (isHovered) {
			hoveredIndex = index;  
			selectedIndex = hoveredIndex;
			anyButtonHovered = true;
		}
	}

	// Handle control source switching
	if (anyButtonHovered) {
		controlByMouse = true;
	}
	else {
		hoveredIndex = -1;

		if (controlByMouse) {
			controlByMouse = false;
			selectedIndex = -1;
		}
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

	if (transitioning) {
		transitionTime += dt;
		float t = transitionTime / transitionDuration;
		if (t >= 1.0f) {
			t = 1.0f;
			transitioning = false;
			currentMenuState = nextMenuState;
		}

		for (DrawableObject* obj : objectsList) {
			MenuState objState = obj->getMenuState();

			if (objState == MenuState::NONE) {
				continue;
			}

			if (objState == currentMenuState) {
				obj->setAlpha(1.0f - t);
			}
			else if (objState == nextMenuState) {
				obj->setAlpha(t);
			}
			else {
				obj->setAlpha(0.0f);
			}
		}
	}
	else {
		for (DrawableObject* obj : objectsList) {
			MenuState objState = obj->getMenuState();

			if (objState == MenuState::NONE) { //Doesn't affect by any states
				obj->setAlpha(1.0f);
				continue;
			}

			obj->setAlpha(objState == currentMenuState ? 1.0f : 0.0f);
			
			UIButton* button = dynamic_cast<UIButton*>(obj);

			if (button) {
				button->setEnable(objState == currentMenuState ? true : false);
			}
		}
	}

	cout << "SelectedIndex: " << selectedIndex << " HoveredIndex: " << hoveredIndex << endl;

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

	for (UIButton*& button : mainButtons) {
		button = nullptr;
	}

	for (UIButton*& button : optionsButtons) {
		button = nullptr;
	}

	for (UIButton*& button : audioButtons) {
		button = nullptr;
	}

	for (UIButton*& button : controlsButtons) {
		button = nullptr;
	}

	for (UIButton*& button : creditsButton) {
		button = nullptr;
	}

	objectsList.clear();
	buttonsList.clear();
	mainButtons.clear();
	optionsButtons.clear();
	audioButtons.clear();
	controlsButtons.clear();
	creditsButton.clear();
}

void LevelMainMenu::levelUnload() {
	GameEngine::getInstance()->clearMesh();
}

void LevelMainMenu::isReceivingNoInputs() {
	
}

void LevelMainMenu::handleKey(char key) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	
	list<UIButton*>* currentList = nullptr;

	switch (currentMenuState) {
	case MenuState::MAIN:
		currentList = &mainButtons;
		break;
	case MenuState::OPTIONS:
		currentList = &optionsButtons;
		break;
	case MenuState::AUDIO:
		currentList = &audioButtons;
		break;
	case MenuState::CONTROLS:
		currentList = &controlsButtons;
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		break;
	default:
		return;
	}

	UIButton* selectedButton = nullptr;

	if (selectedIndex >= 0 && selectedIndex < currentList->size()) {
		auto it = buttonsList.begin();
		std::advance(it, selectedIndex);

		selectedButton = *it;
	}

	/*switch (currentMenuState) {
	case MAIN:
		switch (key) {
		case 'w':
			changeSelection(-1);
			break;
		case 's':
			changeSelection(1);
			break;
		case 'S':
			if (selectedButton && selectedButton->getMouseOver()) {
				selectedButton->OnClick();
			}
			break;
		}
		break;
	case OPTIONS:

		break;
	case AUDIO:
		break;
	case CONTROLS:
		break;
	case CREDITS:
		break;
	default:
		break;
	}*/

	switch (key) {
	case 'a':
		changeMenuState(MenuState::OPTIONS);
		break;
	case 'd':
		changeMenuState(MenuState::MAIN);
		break;
	case 'w':
		changeSelection(-1);
		break;
	case 's':
		changeSelection(1);
		break;
	case 'S':
		if (selectedButton && selectedButton->getMouseOver()) {
			selectedButton->OnClick();
		}
		break;
	}
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

	/*for (UIButton* button : buttonsList) {
		if (button->getMouseOver()) {
			if (type == 0) {
				GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART;
			}
		}
	}*/

	list<UIButton*>* currentList = nullptr;

	switch (currentMenuState) {
	case MenuState::MAIN:
		currentList = &mainButtons;
		break;
	case MenuState::OPTIONS:
		currentList = &optionsButtons;
		break;
	case MenuState::AUDIO:
		currentList = &audioButtons;
		break;
	case MenuState::CONTROLS:
		currentList = &controlsButtons;
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		break;
	default:
		return;
	}

	if (selectedIndex >= 0 && selectedIndex < currentList->size()) {
		auto it = buttonsList.begin();
		std::advance(it, selectedIndex);

		UIButton* selectedButton = *it;

		if (selectedButton && selectedButton->getMouseOver()) {
			if (type == 0) {
				selectedButton->OnClick();
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

void LevelMainMenu::changeMenuState(MenuState targetState) {
	if (targetState == currentMenuState || transitioning) return;

	nextMenuState = targetState;
	transitionTime = 0.0f;
	transitioning = true;
}

MenuState LevelMainMenu::getMenuState() const {
	return currentMenuState;
}

void LevelMainMenu::changeSelection(int direction) {

	list<UIButton*>* currentList = nullptr;

	switch (currentMenuState) {
	case MenuState::MAIN:
		currentList = &mainButtons;
		break;
	case MenuState::OPTIONS:
		currentList = &optionsButtons;
		break;
	case MenuState::AUDIO:
		currentList = &audioButtons;
		break;
	case MenuState::CONTROLS:
		currentList = &controlsButtons;
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		break;
	default:
		return;
	}


	if (!currentList || currentList->empty()) {
		return;
	}

	for (UIButton* btn : buttonsList) { // Deselect
		btn->setMouseOver(false);
	}

	if (selectedIndex == -1) {
		selectedIndex = 0;
	}
	else {
		selectedIndex += direction;
	}

	if (selectedIndex < 0) {
		selectedIndex = currentList->size() - 1;
	}
	else if (selectedIndex >= currentList->size()) {
		selectedIndex = 0;
	}

	auto it = currentList->begin();
	advance(it, selectedIndex);

	focusedButton = *it;
	focusedButton->setMouseOver(true);
}

