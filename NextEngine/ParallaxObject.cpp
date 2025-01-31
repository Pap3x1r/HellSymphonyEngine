#include "ParallaxObject.h"
#include <iostream>

using namespace std;

ParallaxObject::ParallaxObject(float z, bool vertical) : TexturedObject() {
	this->z = z;
	this->vertical = vertical;
	startPos = glm::vec3(0, 0, z);
}

//void ParallaxObject::setStartPos(glm::vec3 startPos) {
//	this->startPos = startPos;
//}

void ParallaxObject::setPlane(float nearPlane, float farPlane) {
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
}

void ParallaxObject::updateParallax(glm::vec3 camPos, glm::vec3 playerPos) {
	glm::vec3 travelDistance = camPos - startPos;
	
	float distanceFromPlayer = this->getTransform().getPosition().z - playerPos.z;
	float plane;
	if (distanceFromPlayer > 0) {
		plane = farPlane;
	}
	else {
		plane = nearPlane;
	}
	float clippingPlane = camPos.z + plane;

	float parallaxFactor = abs(distanceFromPlayer) / clippingPlane;

	glm::vec3 newPos = startPos + (travelDistance * parallaxFactor);
	cout << newPos.x << " " << newPos.y << " " << newPos.z << endl;
	if (vertical) {
		this->getTransform().setPosition(glm::vec3(newPos.x, 0.0f, startPos.z));
	}
	else {
		this->getTransform().setPosition(glm::vec3(newPos.x, newPos.y, startPos.z));
	}
	return;
}

void ParallaxObject::setTexture(string path) {
	TexturedObject::setTexture(path);
}
void ParallaxObject::initAnimation(int row, int column) {
	TexturedObject::initAnimation(row, column);
}
void ParallaxObject::render(glm::mat4 globalModelTransform) {
	TexturedObject::render(globalModelTransform);
}
Animation* ParallaxObject::getAnimationComponent() {
	return TexturedObject::getAnimationComponent();
}
bool ParallaxObject::isAnimated() {
	return TexturedObject::isAnimated();
}