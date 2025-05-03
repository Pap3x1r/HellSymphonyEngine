#include "UIButton.h"

void UIButton::update(float dt) {
	
}

	bool UIButton::isHovered(int mouseX, int mouseY) {

		float windowWidth = GameEngine::getInstance()->getWindowWidth();
		float windowHeight = GameEngine::getInstance()->getWindowHeight();

		float worldMinX = -8;
		float worldMaxX = 8;

		float worldMinY = -4.5;
		float worldMaxY = 4.5;
	
		float worldX = (mouseX / windowWidth) * (worldMaxX - worldMinX) + worldMinX;
		float worldY = (1 - (mouseY / windowHeight)) * (worldMaxY - worldMinY) + worldMinY;

		glm::vec3 position = getTransform().getPosition();
		glm::vec3 scale = getTransform().getScale();

		//std::cout << "Position: " << position.x << ", " << position.y << std::endl;
		//std::cout << "Scale: " << scale.x << ", " << scale.y << std::endl;
		//std::cout << "Mouse: " << mouseX << ", " << mouseY << std::endl;
		//std::cout << "MouseWorld: " << worldX << ", " << worldY << std::endl;

		float halfWidth = scale.x * 0.5f;
		float halfHeight = scale.y * 0.5f;

		if (worldX > position.x - halfWidth && worldX < position.x + halfWidth &&
			worldY > position.y - halfHeight && worldY < position.y + halfHeight) {
			//cout << "Hovered" << endl;
			mouseOver = true;
			return true;
		}

		//cout << "Not hovered" << endl;
		mouseOver = false;
		return false;
	}

	bool UIButton::getMouseOver() const {
		return mouseOver;
	}