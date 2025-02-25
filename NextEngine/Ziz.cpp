#include "Ziz.h"

Ziz::Ziz() {
	setName("Ziz");
	health = new Health(1000);
	setTexture("../Resource/Texture/Ziz_Idle.png");
	getTransform().setScale(glm::vec3(10.0f, 10.0f, 1.0f));
	addColliderComponent();
	getColliderComponent()->setDimension(0.5f, 0.5f);
	//getColliderComponent()->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	setDrawCollider(true);
	initAnimation(1, 1);
	getAnimationComponent()->addState("idle", 0, 1);
	//Physics
	addPhysicsComponent();
	getPhysicsComponent()->setGravity(glm::vec2(0.0f, -0.02f));

	currentState = new BossStateMachine();
	currentState->changeState(ZizIdleState::getInstance(), this);
}

Ziz::~Ziz() {
	delete health;
	delete currentLevel;
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