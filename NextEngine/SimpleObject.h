#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
class SimpleObject :public DrawableObject {
	glm::vec3 color;
	float alpha = 1.0f; //Default alpha
public:
	SimpleObject();
	SimpleObject(string name);
	~SimpleObject();
	void setColor(float r, float g, float b);
	void render(glm::mat4 globalModelTransform);
	void setAlpha(float value) {
		alpha = value;
	}

	float getAlpha() const {
		return alpha;
	}
};

