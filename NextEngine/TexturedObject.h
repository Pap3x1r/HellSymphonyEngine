#pragma once

#include "Animation.h"
#include "DrawableObject.h"
#include "Physics.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>


class TexturedObject : public DrawableObject
{	
	glm::vec3 spriteOffset;
	unsigned int texture;
	Animation* animation; // Might use vector in the future to support multiple animation state
	float hitEffectStrength = 0;
	/*bool animated = false;
	int rowCount;
	int colCount;
	float offsetX;
	float offsetY;*/

public:
	TexturedObject();
	TexturedObject(std::string name);
	~TexturedObject();
	void setTexture(std::string path);
	void setTexture(string path, int row, int col, int startFrame);
	void setTexture(string path, int row, int col, int startFrame, bool loop);
	void initAnimation(int row, int column);
	void render(glm::mat4 globalModelTransform);
	Animation* getAnimationComponent();
	bool isAnimated();
	//void setFrame(float row, float column);
	void setSpriteOffset(glm::vec3 vector3);
	void setHitEffectStrength(float value);
	float getHitEffectStrength();
};