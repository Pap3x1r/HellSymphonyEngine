#include "QTEButtonUI.h"
#include "InputManager.h"
#include "GameEngine.h"

QTEButtonUI::QTEButtonUI() {
	setTexture("../Resource/Texture/UI/KeyboardButtons/W.png");
}

QTEButtonUI::QTEButtonUI(int target) {
	changeTextureDefault(target);
}

void QTEButtonUI::update(float dt) {
	
}

void QTEButtonUI::expire() {
	cout << "deleted qte button ui" << endl;
	DrawableObject::destroyObject(this);
}

void QTEButtonUI::changeTextureDefault(int target) {
	InputManager* inputManager = GameEngine::getInstance()->getInputHandler();

	if (inputManager) {
		if (inputManager->getLastInput() == InputDevice::KEYBOARD) {
			cout << "keyboard" << endl;
			switch (target) {
			case 0:
				setTexture("../Resource/Texture/UI/QTEButtons/keyboard/default/W.png");
				break;
			case 1:
				setTexture("../Resource/Texture/UI/QTEButtons/keyboard/default/A.png");
				break;
			case 2:
				setTexture("../Resource/Texture/UI/QTEButtons/keyboard/default/S.png");
				break;
			case 3:
				setTexture("../Resource/Texture/UI/QTEButtons/keyboard/default/D.png");
				break;
			default:
				break;
			}
		}
		else {
			cout << "controller" << endl;
			switch (target) {
			case 0:
				setTexture("../Resource/Texture/UI/QTEButtons/controller/default/Up.png");
				break;
			case 1:
				setTexture("../Resource/Texture/UI/QTEButtons/controller/default/Left.png");
				break;
			case 2:
				setTexture("../Resource/Texture/UI/QTEButtons/controller/default/Down.png");
				break;
			case 3:
				setTexture("../Resource/Texture/UI/QTEButtons/controller/default/Right.png");
				break;
			default:
				break;
			}
		}
	}


	
}

void QTEButtonUI::changeTextureFailure(int target) {
	InputManager* inputManager = GameEngine::getInstance()->getInputHandler();

	if (inputManager) {
		if (inputManager->getLastInput() == InputDevice::KEYBOARD) {
			switch (target) {
			case 0:
				setTexture("../Resource/Texture/UI/QTEButtons/keyboard/failure/W.png");
				break;
			case 1:
				setTexture("../Resource/Texture/UI/QTEButtons/keyboard/failure/A.png");
				break;
			case 2:
				setTexture("../Resource/Texture/UI/QTEButtons/keyboard/failure/S.png");
				break;
			case 3:
				setTexture("../Resource/Texture/UI/QTEButtons/keyboard/failure/D.png");
				break;
			default:
				break;
			}
		}
		else {
			switch (target) {
			case 0:
				setTexture("../Resource/Texture/UI/QTEButtons/controller/failure/Up.png");
				break;
			case 1:
				setTexture("../Resource/Texture/UI/QTEButtons/controller/failure/Left.png");
				break;
			case 2:
				setTexture("../Resource/Texture/UI/QTEButtons/controller/failure/Down.png");
				break;
			case 3:
				setTexture("../Resource/Texture/UI/QTEButtons/controller/failure/Right.png");
				break;
			default:
				break;
			}
		}
	}

	
}

void QTEButtonUI::changeTextureSuccess(int target) {
	InputManager* inputManager = GameEngine::getInstance()->getInputHandler();

	if (inputManager) {
		if (inputManager->getLastInput() == InputDevice::KEYBOARD) {
			switch (target) {
			case 0:
				setTexture("../Resource/Texture/UI/QTEButtons/keyboard/success/W.png");
				break;
			case 1:
				setTexture("../Resource/Texture/UI/QTEButtons/keyboard/success/A.png");
				break;
			case 2:
				setTexture("../Resource/Texture/UI/QTEButtons/keyboard/success/S.png");
				break;
			case 3:
				setTexture("../Resource/Texture/UI/QTEButtons/keyboard/success/D.png");
				break;
			default:
				break;
			}
		}
		else {
			switch (target) {
			case 0:
				setTexture("../Resource/Texture/UI/QTEButtons/controller/success/Up.png");
				break;
			case 1:
				setTexture("../Resource/Texture/UI/QTEButtons/controller/success/Left.png");
				break;
			case 2:
				setTexture("../Resource/Texture/UI/QTEButtons/controller/success/Down.png");
				break;
			case 3:
				setTexture("../Resource/Texture/UI/QTEButtons/controller/success/Right.png");
				break;
			default:
				break;
			}
		}
	}

	
}