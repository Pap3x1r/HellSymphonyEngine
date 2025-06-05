#include "LevelCredits.h"
#include "CollisionHandler.h"
#include "GameEngine.h"
#include "GLRenderer.h" 
#include <iostream>
#include <random>
using namespace std;




void LevelCredits::levelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->loadData();
	GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

	SquareBorderMesh* border = new SquareBorderMesh();
	border->loadData();
	GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);

	//cout << "Load Level" << endl;
}

void LevelCredits::levelInit() {
	//Value
	float audioSettingsOffsetY = 0.2f;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Background
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* background1 = new TexturedObject("Background1");
	background1->setTexture("../Resource/Texture/End_Credits.png");
	background1->getTransform().setScale(glm::vec3(1.6f * 10, 3.605f * 10, 1.0f));
	background1->getTransform().setPosition(glm::vec3(0.0f, startY, 1.0f));
	background1->setMenuState(MenuState::NONE);
	objectsList.push_back(background1);
	credits = background1;

	/*TexturedObject* background2 = new TexturedObject("Background2");
	background2->setTexture("../Resource/Texture/newMainMenuBGOnly.png");
	background2->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background2->setMenuState(MenuState::OPTIONS);
	background2->addMenuStateToVec(MenuState::AUDIO);
	background2->addMenuStateToVec(MenuState::CREDITS);
	background2->addMenuStateToVec(MenuState::CONTROLLER);
	background2->addMenuStateToVec(MenuState::KEYBOARD);
	objectsList.push_back(background2);

	TexturedObject* background3 = new TexturedObject("Background3");
	background3->setTexture("../Resource/Texture/MenuController.png");
	background3->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background3->setMenuState(MenuState::CONTROLLER);
	objectsList.push_back(background3);

	TexturedObject* background4 = new TexturedObject("Background4");
	background4->setTexture("../Resource/Texture/MenuMKB.png");
	background4->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background4->setMenuState(MenuState::KEYBOARD);
	objectsList.push_back(background4);*/



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Black Fading Transition
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* blackFade_ = new TexturedObject("Black Fade");
	blackFade_->setTexture("../Resource/Texture/blackFade.png");
	blackFade_->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	blackFade_->setMenuState(MenuState::IGNORE);
	objectsList.push_back(blackFade_);
	blackFade = blackFade_;
	blackFade->setAlpha(1.0f);
	firstStart = true;

	secondStart = false;
	isHolding = false;
	//GameEngine::getInstance()->freezeGameForSecond(1.6f);
}

void LevelCredits::levelUpdate() {
	dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	timeK += dt;

	if (firstStart) {
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
			blackFadeTransitionTime = 0.0f;
		}

		return;
	}

	credits->getTransform().translate(glm::vec3(0.0f, velocityY * dt * 0.1f, 0.0f));

	if (credits->getTransform().getPosition().y >= endY) {
		credits->getTransform().setPosition(glm::vec3(0.0f, endY, 0.0f));
		secondStart = true;
	}

	if (secondStart) {
		blackFadeTransitionTime += dt;
		float t = blackFadeTransitionTime / blackFadeTransitionDuration;
		bool finishBlackFade = false;
		if (t >= 1.0f) {
			t = 1.0f;
			finishBlackFade = true;
		}

		blackFade->setAlpha(t);

		if (finishBlackFade) {
			secondStart = false;
			newGame();
		}

		return;
	}

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
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
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
			focusedButton = nullptr;
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

			if (find(objStateVec.begin(), objStateVec.end(), MenuState::IGNORE) != objStateVec.end()) {
				UIButton* button = dynamic_cast<UIButton*>(obj);
				if (button) {
					button->setEnable(true);
				}
				continue;
			}

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

			if (find(objStateVec.begin(), objStateVec.end(), MenuState::IGNORE) != objStateVec.end()) {
				UIButton* button = dynamic_cast<UIButton*>(obj);
				if (button) {
					button->setEnable(true);
				}
				continue;
			}

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

	for (SliderObject* obj : slidersList) {
		obj->update(dt);


		if (SoundManager::GetInstance()) {
			if (obj == masterSlider) {
				SoundManager::GetInstance()->setMasterVolume(masterSlider->getValue());
			}
			else if (obj == musicSlider) {
				SoundManager::GetInstance()->setMusicVolume(musicSlider->getValue());
			}
			else if (obj == sfxSlider) {
				SoundManager::GetInstance()->setSoundEffectVolume(sfxSlider->getValue());
			}
			else if (obj == ambientSlider) {
				SoundManager::GetInstance()->setAmbientVolume(ambientSlider->getValue());
			}
		}
	}


	//cout << "SelectedIndex: " << selectedIndex << " HoveredIndex: " << hoveredIndex << endl;

	//handleObjectCollision(objectsList);

}

void LevelCredits::levelDraw() {
	GameEngine::getInstance()->render(objectsList);
}

void LevelCredits::levelFree() {

	for (DrawableObject* obj : objectsList) {
		delete obj;
	}

	for (SliderObject*& obj : slidersList) {
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

	for (UIButton*& button : controllerButtons) {
		button = nullptr;
	}

	for (UIButton*& button : keyboardButtons) {
		button = nullptr;
	}

	for (UIButton*& button : creditsButton) {
		button = nullptr;
	}

	slidersList.clear();
	objectsList.clear();
	buttonsList.clear();
	mainButtons.clear();
	optionsButtons.clear();
	audioButtons.clear();
	controllerButtons.clear();
	keyboardButtons.clear();
	creditsButton.clear();
}

void LevelCredits::levelUnload() {
	GameEngine::getInstance()->clearMesh();
}

void LevelCredits::isReceivingNoInputs() {

}

void LevelCredits::handleKey(char key) {
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
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		break;
	default:
		return;
	}

	/*UIButton* selectedButton = nullptr;

	if (selectedIndex >= 0 && selectedIndex < currentList->size()) {
		auto it = buttonsList.begin();
		std::advance(it, selectedIndex);

		selectedButton = *it;
	}*/

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
	case 'r': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART; ; break;
	case 'a':
		if (isHolding == false) {
			if (focusedButton) {
				SliderObject* slider = focusedButton->getSlider();
				if (slider) {
					slider->setValue(slider->getValue() - 0.025f);
				}
			}
			isHolding = true;
		}

		if (isHolding == true) {
			holdButtonTimer += dt;
			if (holdButtonTimer >= holdButtonThreshold) {
				if (focusedButton) {
					SliderObject* slider = focusedButton->getSlider();
					if (slider) {
						slider->setValue(slider->getValue() - 0.005f);
					}
				}
			}
		}


		break;
	case 'd':

		if (isHolding == false) {
			if (focusedButton) {
				SliderObject* slider = focusedButton->getSlider();
				if (slider) {
					slider->setValue(slider->getValue() + 0.025f);
				}
			}
			isHolding = true;
		}

		if (isHolding == true) {
			holdButtonTimer += dt;
			if (holdButtonTimer >= holdButtonThreshold) {
				if (focusedButton) {
					SliderObject* slider = focusedButton->getSlider();
					if (slider) {
						slider->setValue(slider->getValue() + 0.005f);
					}
				}
			}
		}


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
		else if (currentMenuState == CONTROLLER) {
			changeMenuState(MenuState::OPTIONS);
		}
		else if (currentMenuState == KEYBOARD) {
			changeMenuState(MenuState::OPTIONS);
		}
		else if (currentMenuState == CREDITS) {
			changeMenuState(MenuState::MAIN);
		}
		break;
	case 'S':
		/*if (selectedButton && selectedButton->getMouseOver()) {
			selectedButton->OnClick();
		}*/

		if (focusedButton && focusedButton->getMouseOver()) {
			focusedButton->OnClick();
		}

		break;
	case 'I':
		if (isHolding == true) {
			isHolding = false;
		}
		if (holdButtonTimer > 0) {
			holdButtonTimer = 0;
		}
		break;
	}
}

void LevelCredits::handleControllerButton(SDL_GameControllerButton button) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();

}


void LevelCredits::handleMouse(int type, int x, int y) {
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
		if (type == 1) {
			changeMenuState(MenuState::OPTIONS);
		}
		break;
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		if (type == 1) {
			changeMenuState(MenuState::OPTIONS);
		}
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
		if (type == 1) {
			changeMenuState(MenuState::OPTIONS);
		}
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		if (type == 1) {
			changeMenuState(MenuState::MAIN);
		}
		break;
	default:
		return;
	}


	if (selectedIndex >= 0 && selectedIndex < currentList->size()) {
		auto it = currentList->begin();
		std::advance(it, selectedIndex);

		UIButton* onButton = *it;

		if (onButton && onButton->getMouseOver()) {
			if (type == 0) {
				onButton->OnClick();
				if (onButton->getHandle()) {
					focusedHandle = *it;
				}
			}
		}
	}

	if (focusedHandle) {
		//cout << focusedHandle->getName() << endl;
		if (type == 2) {
			focusedHandle = nullptr;
		}

		if (type == 4) {

			SliderObject* handleSlider = focusedHandle->getSlider();

			if (handleSlider) {
				//cout << "has slider" << endl;
			}

			glm::vec2 gamePos = convertMouseToGameSpace(x, y);

			for (SliderObject* slider : slidersList) {

				if (focusedHandle->getSlider() == slider) {
					//cout << "Button's Slider: " << focusedHandle->getSlider()->getName() << " Slider:" << slider->getName() << endl;

					glm::vec3 handlePos = slider->getObject(2)->getTransform().getPosition(); // 2 = handle
					glm::vec3 bgPos = slider->getObject(0)->getTransform().getPosition(); // 0 = background

					float sliderLeft = bgPos.x - slider->getOriginalWidth().x * 0.5f;
					float sliderRight = bgPos.x + slider->getOriginalWidth().x * 0.5f;

					//cout << "Mouse Pos: " << gamePos.x << "," << gamePos.y << "Slider X Left:" << sliderLeft << ", Slider X Right:" << sliderRight << endl;


					if (gamePos.x <= sliderLeft) {
						slider->setValue(0.0f);
					}
					else if (gamePos.x >= sliderRight) {
						slider->setValue(1.0f);
					}
					else if (gamePos.x >= sliderLeft && gamePos.x <= sliderRight) {
						float newValue = (gamePos.x - sliderLeft) / (sliderRight - sliderLeft);
						slider->setValue(newValue);
					}
					slider->update(dt);
				}
			}
		}
	}
}

void LevelCredits::handleAnalogStick(int type, char key) {
	float dt_ = GameEngine::getInstance()->getTime()->getDeltaTime();


}

void LevelCredits::addObject(DrawableObject* obj) {
	objectsList.push_back(obj);
}

void LevelCredits::changeMenuState(MenuState targetState) {
	if (targetState == currentMenuState || transitioning) return;

	selectedIndex = -1;

	nextMenuState = targetState;
	transitionTime = 0.0f;
	transitioning = true;
}

MenuState LevelCredits::getMenuState() const {
	return currentMenuState;
}

void LevelCredits::changeSelection(int direction) {

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
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
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

	if (!focusedButton->getEnable()) {
		selectedIndex += direction;
	}

	if (focusedButton->getHandle()) {
		selectedIndex += direction;
	}

	if (selectedIndex < 0) {
		selectedIndex = currentList->size() - 1;
	}
	else if (selectedIndex >= currentList->size()) {
		selectedIndex = 0;
	}

	it = currentList->begin();
	advance(it, selectedIndex);

	focusedButton = *it;
	focusedButton->setMouseOver(true);
	//cout << focusedButton->getName() << endl;
}

glm::vec2 LevelCredits::convertMouseToGameSpace(int mouseX, int mouseY) {
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