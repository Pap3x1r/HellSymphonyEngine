#pragma once
#include "DrawableObject.h"
#include "Lucifer.h"
#include "RadiantLaser.h"
#include <iostream>

class BeamRadiant : public TexturedObject {
private:

	Lucifer* lucifer;

	float timer;
	bool spawnedLaser;
	float spawnLaser;

public:

	BeamRadiant();

	void update(float dt);
};