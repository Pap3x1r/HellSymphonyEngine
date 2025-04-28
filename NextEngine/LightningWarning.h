#pragma once
#include "TexturedObject.h"
#include <iostream>

class LightningWarning : public TexturedObject {
private:
	float timer = 0.08f * 12 * 4;
public:
	LightningWarning() {
		setTexture("../Resource/Ziz/Swoop Warning.png");
		getTransform().setPosition(glm::vec3(-7.0f, 0.0f, 0.0f));
	}

	void update(float dt) {
		timer -= dt;
		//cout << "Timer: " << timer << endl;
		if (timer <= 0) {
			DrawableObject::destroyObject(this);
		}
	}
};