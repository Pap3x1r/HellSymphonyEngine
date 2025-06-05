#pragma once
#include "TexturedObject.h"

class IceFloorWarning : public TexturedObject {
private:
	float timer = 0.8f;
public:
	IceFloorWarning() {
		setTexture("../Resource/Texture/Lucifer/VFX/Warning.png");
		getTransform().setPosition(glm::vec3(0.0f, -3.0f, 0.0f));
		getTransform().setScale(glm::vec3(1.5f, 1.5f, 1.0f));
	}



	void update(float dt) {
		timer -= dt;
		//cout << "Timer: " << timer << endl;
		if (timer <= 0) {
			DrawableObject::destroyObject(this);
		}
	}
};