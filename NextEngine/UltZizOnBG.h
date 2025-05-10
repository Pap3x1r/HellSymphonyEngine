#pragma once
#include "DrawableObject.h"
#include <iostream>
#include "Ziz.h"

class UltZizOnBG : public TexturedObject {
private:
	bool enteredScreen;
	bool hasSummonedLightning;
	bool hasExited;
	bool readyToExit;

	float startUpTimer;
	float startUpDuration;
	float delayBeforeLightning;
	float exitTimer;
	float exitDuration;
	float delayAfterLightning;
	int timesSummonedLightining;
	// 12 = 1 sec
	float t;

	glm::vec3 startPos;
	glm::vec3 endPos;
	glm::vec3 newPos;

	glm::vec3 startPos2;
	glm::vec3 endPos2;
	glm::vec3 newPos2;

	Ziz* ziz;
public:
	
	UltZizOnBG();
	UltZizOnBG(Ziz* boss);

	void update(float dt);
};