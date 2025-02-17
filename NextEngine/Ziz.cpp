#include "Ziz.h"

Ziz::Ziz() {

}

Ziz::~Ziz() {
	delete health;
}

void Ziz::setLevel(Level* newLevel) {
	if (!newLevel) {
		cerr << "Error: setLevel() received a nullptr.";
		return;
	}
	currentLevel = newLevel;
}

Level* Ziz::getLevel() const {
	return currentLevel;
}

void Ziz::setFacingRight(bool value) {
	isFacingRight = value;

	if (isFacingRight) {
		getTransform().setScale(glm::vec3(4.5f, -4.5f, 1.0f));
	}
	else {
		getTransform().setScale(glm::vec3(-4.5f, -4.5f, 1.0f));
	}
}

bool Ziz::getFacingRight() const {
	return isFacingRight;
}

BossStateMachine* Ziz::getStateMachine() const {
	return currentState;
}