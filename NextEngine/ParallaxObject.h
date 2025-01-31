#pragma once
#include "TexturedObject.h"

class ParallaxObject : public TexturedObject {
private:
	//glm::vec3 camPos;
	//glm::vec3 playerPos;
	float z;
	bool vertical;
	glm::vec3 startPos;
	float nearPlane;
	float farPlane;

public:
	ParallaxObject(float z, bool vertical);
	//void setStartPos(glm::vec3 startPos);
	void setPlane(float nearPlane, float farPlane);
	void updateParallax(glm::vec3 camPos, glm::vec3 playerPos);
	void setTexture(string path);
	void initAnimation(int row, int column);
	void render(glm::mat4 globalModelTransform);
	Animation* getAnimationComponent();
	bool isAnimated();
};