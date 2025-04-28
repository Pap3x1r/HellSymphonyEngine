#pragma once
#include "DrawableObject.h"
#include <iostream>
#include "Ziz.h"

class UltZizOnBG : public TexturedObject {
private:
	bool enteredScreen;
	bool hasSummonedLightning;

	float startUpTimer;
	float startUpDuration;
	float delayBeforeLightning;
	// 12 = 1 sec
	float t;

	glm::vec3 startPos;
	glm::vec3 endPos;
	glm::vec3 newPos;

	Ziz* ziz;
public:
	
	UltZizOnBG();
	UltZizOnBG(Ziz* boss);

	void update(float dt);
};