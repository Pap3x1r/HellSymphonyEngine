#include "QTEButtonUI.h"

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
	switch (target) {
	case 0:
		setTexture("../Resource/Texture/UI/QTEButtons/default/W.png");
		break;
	case 1:
		setTexture("../Resource/Texture/UI/QTEButtons/default/A.png");
		break;
	case 2:
		setTexture("../Resource/Texture/UI/QTEButtons/default/S.png");
		break;
	case 3:
		setTexture("../Resource/Texture/UI/QTEButtons/default/D.png");
		break;
	default:
		break;
	}
}

void QTEButtonUI::changeTextureFailure(int target) {
	switch (target) {
	case 0:
		setTexture("../Resource/Texture/UI/QTEButtons/failure/W.png");
		break;
	case 1:
		setTexture("../Resource/Texture/UI/QTEButtons/failure/A.png");
		break;
	case 2:
		setTexture("../Resource/Texture/UI/QTEButtons/failure/S.png");
		break;
	case 3:
		setTexture("../Resource/Texture/UI/QTEButtons/failure/D.png");
		break;
	default:
		break;
	}
}

void QTEButtonUI::changeTextureSuccess(int target) {
	switch (target) {
	case 0:
		setTexture("../Resource/Texture/UI/QTEButtons/success/W.png");
		break;
	case 1:
		setTexture("../Resource/Texture/UI/QTEButtons/success/A.png");
		break;
	case 2:
		setTexture("../Resource/Texture/UI/QTEButtons/success/S.png");
		break;
	case 3:
		setTexture("../Resource/Texture/UI/QTEButtons/success/D.png");
		break;
	default:
		break;
	}
}