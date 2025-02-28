#pragma once
#include "TexturedObject.h"

class SwoopWarning : public TexturedObject {
	private:
		float timer = 2.0f;
	public:
		SwoopWarning() {
			setTexture("../Resource/Ziz/Swoop Warning.png");
			getTransform().setPosition(glm::vec3(-7.0f, 0.0f, 0.0f));
			getTransform().setScale(glm::vec3(2.0f, 12.0f, 1.0f));
			cout << "made Warning" << endl;
		}

		SwoopWarning(int side) {
			setTexture("../Resource/Ziz/Swoop Warning.png");
			if (side == -1) {
				getTransform().setPosition(glm::vec3(-7.0f, 0.0f, 0.0f));
			}
			else if (side == 1) {
				getTransform().setPosition(glm::vec3(7.0f, 0.0f, 0.0f));
			}
			
			getTransform().setScale(glm::vec3(2.0f, 12.0f, 1.0f));
		}

		void update(float dt) {
			timer -= dt;
			//cout << "Timer: " << timer << endl;
			if (timer <= 0) {
				DrawableObject::destroyObject(this);
			}
		}
};