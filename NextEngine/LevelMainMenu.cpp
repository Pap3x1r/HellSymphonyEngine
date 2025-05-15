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
	//										Background
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* background1 = new TexturedObject("Background");
	background1->setTexture("../Resource/Texture/newMainMenuBG.png");
	background1->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background1->setMenuState(MenuState::NONE);
	objectsList.push_back(background1);

	TexturedObject* background2 = new TexturedObject();
	background2->setTexture("../Resource/Texture/newMainMenuBGOnly.png");
	background2->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background2->setMenuState(MenuState::OPTIONS);
	background2->addMenuStateToVec(MenuState::AUDIO);
	objectsList.push_back(background2);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Lines
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SimpleObject* line1 = new SimpleObject();
	line1->setColor(1.0f, 1.0f, 1.0f);
	line1->getTransform().setScale(glm::vec3(14.0f, 0.01f, 0.0f));	
	line1->getTransform().setPosition(glm::vec3(0.0f, 3.3f, 0.0f));
	line1->setMenuState(MenuState::OPTIONS);
	objectsList.push_back(line1);

	SimpleObject* line2 = new SimpleObject();
	line2->setColor(1.0f, 1.0f, 1.0f);
	line2->getTransform().setScale(glm::vec3(14.0f, 0.01f, 0.0f));
	line2->getTransform().setPosition(glm::vec3(0.0f, -3.5f, 0.0f));
	line2->setMenuState(MenuState::OPTIONS);
	objectsList.push_back(line2);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Sliders
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SliderObject* masterVolumeSlider = new SliderObject();
	masterVolumeSlider->setScale(glm::vec3(10.0f, 0.5f, 1.0f), 0);
	masterVolumeSlider->setScale(glm::vec3(10.0f, 0.5f, 1.0f), 1);
	masterVolumeSlider->setScale(glm::vec3(0.3f, 1.0f, 1.0f), 2);
	masterVolumeSlider->setColor(glm::vec3(1.0f, 1.0f, 1.0f), -1);
	masterVolumeSlider->setColor(glm::vec3(0.5f, 0.5f, 0.5f), 1);
	masterVolumeSlider->setMenuState(MenuState::AUDIO);
	masterVolumeSlider->setValue(1.0f);
	for (DrawableObject* obj : masterVolumeSlider->getObjectsList()) {
		objectsList.push_back(obj);
	}

	buttonsList.push_back(static_cast<UIButton*>(masterVolumeSlider->getObject(2)));
	audioButtons.push_back(static_cast<UIButton*>(masterVolumeSlider->getObject(2)));
	slider = masterVolumeSlider;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Texts
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* staticSettingsText = new UIText("Static Settings Text");
	SDL_Color staticSettingsTextColor = { 255,255,255,255 };
	staticSettingsText->loadText("SETTINGS", staticSettingsTextColor, 100);
	staticSettingsText->setText("SETTINGS");
	staticSettingsText->setAlpha(1.0f);
	staticSettingsText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	staticSettingsText->getTransform().setPosition(glm::vec3(0.1f, 3.6f, 0.0f));
	staticSettingsText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	staticSettingsText->addColliderComponent();
	staticSettingsText->setMenuState(MenuState::OPTIONS);
	/*staticSettingsText->setDrawCollider(true);
	staticSettingsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(staticSettingsText);

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
	continueText->getTransform().setPosition(glm::vec3(0.25f, 0.0f - 0.6f, 0.0f));
	continueText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	continueText->addColliderComponent();
	continueText->setMenuState(MenuState::MAIN);
	/*continueText->setDrawCollider(true);
	continueText->setCanDrawColliderNew(true);*/
	objectsList.push_back(continueText);

	UIButton* continueButton = new UIButton("Continue Button");
	//continueButton->setTexture("../Resource/Texture/UI/UIButton.png");
	continueButton->getTransform().setPosition(glm::vec3(0.0f, 0.25f - 0.6f, 0.0f));
	continueButton->getTransform().setScale(glm::vec3(1.6f, 0.35f, 0.0f));
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
	playText->getTransform().setPosition(glm::vec3(0.15f, -0.525f - 0.7f, 0.0f));
	playText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	playText->addColliderComponent();
	playText->setMenuState(MenuState::MAIN);
	/*playText->setDrawCollider(true);
	playText->setCanDrawColliderNew(true);*/
	objectsList.push_back(playText);

	UIButton* playButton = new UIButton("New Game Button");
	//playButton->setTexture("../Resource/Texture/UI/UIButton.png");
	playButton->getTransform().setPosition(glm::vec3(0.0f, -0.28f - 0.7f, 0.0f));
	playButton->getTransform().setScale(glm::vec3(1.8f, 0.35f, 0.0f));
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
	settingsText->getTransform().setPosition(glm::vec3(0.41f, -1.05f - 0.8f, 0.0f));
	settingsText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	settingsText->addColliderComponent();
	settingsText->setMenuState(MenuState::MAIN);
	/*settingsText->setDrawCollider(true);
	settingsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(settingsText);

	UIButton* settingsButton = new UIButton("Settings Button");
	//settingsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	settingsButton->getTransform().setPosition(glm::vec3(0.0f, -0.81f - 0.8f, 0.0f));
	settingsButton->getTransform().setScale(glm::vec3(1.3f, 0.35f, 0.0f));
	settingsButton->addColliderComponent();
	settingsButton->setDrawCollider(true);
	settingsButton->setCanDrawColliderNew(true);
	settingsButton->setDraw(false);
	settingsButton->setLabel(settingsText); // Link playText
	settingsButton->setMenuState(MenuState::MAIN);
	settingsButton->setFunction([this]() { changeMenuState(MenuState::OPTIONS);});
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
	creditsText->getTransform().setPosition(glm::vec3(0.45f, -1.58f - 0.9f, 0.0f));
	creditsText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	creditsText->addColliderComponent();
	creditsText->setMenuState(MenuState::MAIN);
	/*creditsText->setDrawCollider(true);
	creditsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(creditsText);

	UIButton* creditsButton = new UIButton("Credits Button");
	//creditsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	creditsButton->getTransform().setPosition(glm::vec3(0.0f, -1.34f - 0.9f, 0.0f));
	creditsButton->getTransform().setScale(glm::vec3(1.2f, 0.35f, 0.0f));
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
	quitText->getTransform().setPosition(glm::vec3(0.14f, -2.1f - 1.0f, 0.0f));
	quitText->getTransform().setScale(glm::vec3(1.0f, 1.0f, 0.0f));
	quitText->addColliderComponent();
	quitText->setMenuState(MenuState::MAIN);
	/*quitText->setDrawCollider(true);
	quitText->setCanDrawColliderNew(true);*/
	objectsList.push_back(quitText);

	UIButton* quitButton = new UIButton("Quit Button");
	//creditsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	quitButton->getTransform().setPosition(glm::vec3(0.0f, -1.85f - 1.0f, 0.0f));
	quitButton->getTransform().setScale(glm::vec3(0.8f, 0.35f, 0.0f));
	quitButton->addColliderComponent();
	quitButton->setDrawCollider(true);
	quitButton->setCanDrawColliderNew(true);
	quitButton->setDraw(false);
	quitButton->setLabel(quitText); // Link playText
	quitButton->setMenuState(MenuState::MAIN);
	objectsList.push_back(quitButton);
	buttonsList.push_back(quitButton);

	mainButtons.push_back(quitButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Audio Button (Settings)
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* audioText = new UIText("Audio Text");
	SDL_Color audioTextColor = { 255,255,255,255 };
	audioText->loadText("Audio", audioTextColor, 100);
	audioText->setText("Audio");
	audioText->setAlpha(1.0f);
	audioText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	audioText->getTransform().setPosition(glm::vec3(-5.5f, 2.15f, 0.0f));
	audioText->getTransform().setScale(glm::vec3(1.0f, 1.0f, 0.0f));
	audioText->addColliderComponent();
	audioText->setMenuState(MenuState::OPTIONS);
	/*audioText->setDrawCollider(true);
	audioText->setCanDrawColliderNew(true);*/
	objectsList.push_back(audioText);

	UIButton* audioButton = new UIButton("Audio Button");
	//audioButton->setTexture("../Resource/Texture/UI/UIButton.png");
	audioButton->getTransform().setPosition(glm::vec3(-5.5f, 2.4f, 0.0f));
	audioButton->getTransform().setScale(glm::vec3(1.0f, 0.35f, 0.0f));
	audioButton->addColliderComponent();
	audioButton->setDrawCollider(true);
	audioButton->setCanDrawColliderNew(true);
	audioButton->setDraw(false);
	audioButton->setLabel(audioText); // Link playText
	audioButton->setMenuState(MenuState::OPTIONS);
	objectsList.push_back(audioButton);
	buttonsList.push_back(audioButton);

	optionsButtons.push_back(audioButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Controller Button (Settings)
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* controllerText = new UIText("Controller Text");
	SDL_Color controllerTextColor = { 255,255,255,255 };
	controllerText->loadText("Controller", controllerTextColor, 100);
	controllerText->setText("Controller");
	controllerText->setAlpha(1.0f);
	controllerText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	controllerText->getTransform().setPosition(glm::vec3(-5.0f, 1.5f, 0.0f));
	controllerText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	controllerText->addColliderComponent();
	controllerText->setMenuState(MenuState::OPTIONS);
	/*controllerText->setDrawCollider(true);
	controllerText->setCanDrawColliderNew(true);*/
	objectsList.push_back(controllerText);

	UIButton* controllerButton = new UIButton("Controller Button");
	//controllerButton->setTexture("../Resource/Texture/UI/UIButton.png");
	controllerButton->getTransform().setPosition(glm::vec3(-5.2f, 1.75f, 0.0f));
	controllerButton->getTransform().setScale(glm::vec3(1.6f, 0.35f, 0.0f));
	controllerButton->addColliderComponent();
	controllerButton->setDrawCollider(true);
	controllerButton->setCanDrawColliderNew(true);
	controllerButton->setDraw(false);
	controllerButton->setLabel(controllerText); // Link playText
	controllerButton->setMenuState(MenuState::OPTIONS);
	objectsList.push_back(controllerButton);
	buttonsList.push_back(controllerButton);

	optionsButtons.push_back(controllerButton);



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

	int index = 0; 
	for (auto it = currentList->begin(); it != currentList->end(); ++it, ++index) {
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

		if (obj->getName() == "Background") {
			//cout << obj->getName() << "'s Alpha:" << obj->getAlpha() << endl;
		}
	}

	if (transitioning) {
		transitionTime += dt;
		float t = transitionTime / transitionDuration;
		bool finish = false;
		if (t >= 1.0f) {
			t = 1.0f;
			finish = true;
		}

		for (DrawableObject* obj : objectsList) {
			MenuState objState = obj->getMenuState();
			vector<MenuState> objStateVec = obj->getMenuStateVec();

			if (find(objStateVec.begin(), objStateVec.end(), MenuState::NONE) != objStateVec.end()) {
				obj->setAlpha(1.0f);
				continue;
			}

			bool inCurrent = objState == currentMenuState ||
				find(objStateVec.begin(), objStateVec.end(), currentMenuState) != objStateVec.end();
			bool inNext = objState == nextMenuState ||
				find(objStateVec.begin(), objStateVec.end(), nextMenuState) != objStateVec.end();
			
			if (inCurrent && inNext) { //If the object has many states.
				obj->setAlpha(1.0f);
			}
			else if (inCurrent) {
				obj->setAlpha(1.0f - t);
			}
			else if (inNext) {
				obj->setAlpha(t);
			}
			else {
				obj->setAlpha(0.0f);
			}
		}

		if (finish) {
			transitioning = false;
			currentMenuState = nextMenuState;
		}
	}
	else {
		for (DrawableObject* obj : objectsList) {
			MenuState objState = obj->getMenuState();
			vector<MenuState> objStateVec = obj->getMenuStateVec();

			if (find(objStateVec.begin(), objStateVec.end(), MenuState::NONE) != objStateVec.end()) {//Doesn't affect by any states
				obj->setAlpha(1.0f);
				continue;
			}

			bool inCurrent = objState == currentMenuState ||
				find(objStateVec.begin(), objStateVec.end(), currentMenuState) != objStateVec.end();

			obj->setAlpha(inCurrent ? 1.0f : 0.0f);

			/*if (inCurrent) {
				cout << obj->getName() << "'s MenuState:" << obj->getMenuState() << " Alpha:" << obj->getAlpha() << endl;
				for (auto o : obj->getMenuStateVec()) {
					cout << o << endl;
				}
			}*/
			
			UIButton* button = dynamic_cast<UIButton*>(obj);

			if (button) {
				button->setEnable(inCurrent ? true : false);
			}
		}
	}

	for (DrawableObject* obj : slider->getObjectsList()) {
		/*cout << obj->getName() << "'s MenuState:" << obj->getMenuState() << " Alpha:" << obj->getAlpha() << endl;
		for (auto o : obj->getMenuStateVec()) {
			cout << o << endl;
		}*/
	}

	//cout << "SelectedIndex: " << selectedIndex << " HoveredIndex: " << hoveredIndex << endl;

	slider->update(dt);

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
	case 'c':
		if (currentMenuState == MAIN) {
			changeMenuState(MenuState::AUDIO);
		}
		else if (currentMenuState == OPTIONS) {
			changeMenuState(MenuState::AUDIO);
		}

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
	case 'q':
		if (currentMenuState == OPTIONS) {
			changeMenuState(MenuState::MAIN);
		}
		else if (currentMenuState == AUDIO) {
			changeMenuState(MenuState::OPTIONS);
		}
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
		if (type == 1) {
			changeMenuState(MenuState::MAIN);
		}
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
		auto it = currentList->begin();
		std::advance(it, selectedIndex);

		UIButton* selectedButton = *it;

		if (selectedButton && selectedButton->getMouseOver()) {
			if (type == 0) {
				selectedButton->OnClick();
			}
			else if (type == 4) {
				glm::vec2 gamePos = convertMouseToGameSpace(x, y);

				glm::vec3 handlePos = slider->getObject(2)->getTransform().getPosition(); // 2 = handle
				glm::vec3 bgPos = slider->getObject(0)->getTransform().getPosition(); // 0 = background

				float sliderLeft = bgPos.x - slider->getOriginalWidth().x * 0.5f;
				float sliderRight = bgPos.x + slider->getOriginalWidth().x * 0.5f;

				cout << "Mouse Pos: " << gamePos.x << "," << gamePos.y << "Slider X Left:" << sliderLeft << ", Slider X Right:" << sliderRight << endl;

				

				if (gamePos.x >= sliderLeft && gamePos.x <= sliderRight) {
					float newValue = (gamePos.x - sliderLeft) / (sliderRight - sliderLeft);
					slider->setValue(newValue);
					slider->update(dt);
				}

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

	selectedIndex = -1;

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
	//cout << focusedButton->getName() << endl;
}

glm::vec2 LevelMainMenu::convertMouseToGameSpace(int mouseX, int mouseY) {
	int windowWidth = GameEngine::getInstance()->getWindowWidth();
	int windowHeight = GameEngine::getInstance()->getWindowHeight();

	const float targetAspect = 16.0f / 9.0f;
	float windowAspect = static_cast<float>(windowWidth) / windowHeight;

	float gameWidth = 16.0f;
	float gameHeight = 9.0f;

	float scale;
	float offsetX = 0;
	float offsetY = 0;

	if (windowAspect > targetAspect) {
		// Black bars on left/right
		scale = windowHeight / gameHeight;
		offsetX = (windowWidth - gameWidth * scale) / 2.0f;
	}
	else {
		// Black bars on top/bottom
		scale = windowWidth / gameWidth;
		offsetY = (windowHeight - gameHeight * scale) / 2.0f;
	}

	// Convert to normalized game coordinates
	float gameX = (mouseX - offsetX) / scale;
	float gameY = (mouseY - offsetY) / scale;

	// Flip Y if window origin is top-left but game origin is center
	gameY = gameHeight - gameY;

	// Shift origin to center
	gameX -= gameWidth / 2.0f;
	gameY -= gameHeight / 2.0f;

	return glm::vec2(gameX, gameY);
}