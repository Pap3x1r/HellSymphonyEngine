#include "UIButton.h"

void UIButton::update(float dt) {
	
}

bool UIButton::isMouseOver() {

	glm::vec3 pos = getTransform().getPosition();
	glm::vec3 nice;

	return mouseOver;
}