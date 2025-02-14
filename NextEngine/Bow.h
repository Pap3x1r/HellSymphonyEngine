#pragma once
#include "Arrow.h"

class Player;

class Bow {
	float rapidShotTimer = 0.15f;
	float rapidShotTimeElapsed = rapidShotTimer;
	bool rapidShotReady = false;

	float currentRapidOverheat = 0.0f;
	float maxRapidOverheat = 100.0f;
	float overheatPerArrow = 7.5f;
	float normalDecreaseRate = 25.0f;
	float overheatDecreaseRate = 17.5f;
	bool isOverheat = false;



	bool rapidShotDebugMode = false;

public:
	Bow();
	void update(float dt, Player* player);

	void setEnableDebug();

	DrawableObject* arrowShot(float damage_, Player* player, float speed);

	bool getRapidShotReady() const;
	bool getIsOverheat() const;
};
