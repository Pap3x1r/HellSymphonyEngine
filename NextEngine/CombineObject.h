#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class CombineObject : public DrawableObject
{
	glm::vec3 color;
	glm::vec3 color2;

public:
	CombineObject();
	CombineObject(string name);
	~CombineObject();
	void setColor(float r, float g, float b);
	void setColor2(float r, float g, float b);
	void render(glm::mat4 globalModelTransform);
};
