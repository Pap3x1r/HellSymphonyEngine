#include "Boss.h"


Boss::Boss() {
	//health
	health = nullptr;
	//level
	currentLevel = nullptr;
	//StateMachine
	currentState = nullptr;
	cout << "Boss Parent Created" << endl;
}

Boss::~Boss() {
	delete health;
}


void Boss::setFacingRight(bool value) {

}

bool Boss::getFacingRight() const {
	return isFacingRight;
}


void Boss::setLevel(Level* newLevel) {
	if (!newLevel) {
		cerr << "Error: setLevel() received a nullptr.";
		return;
	}
	currentLevel = newLevel;
}


Level* Boss::getLevel() const {
	return currentLevel;
}

BossStateMachine* Boss::getStateMachine() const {
	return currentState;
}