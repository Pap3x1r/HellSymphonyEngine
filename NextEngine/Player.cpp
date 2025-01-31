#include "Player.h"

Player::Player(float hp) {
	health = new Health(hp);

	setTexture("../Resource/Texture/dante_idle.png");
	getTransform().setScale(glm::vec3(4.5f, -4.5f, 1.0f));
	//Anim
	initAnimation(8, 1);
	getAnimationComponent()->addState("idle", 0, 8);
	getAnimationComponent()->setState("idle");
	//Collider
	addColliderComponent();
	getColliderComponent()->setDimension(0.15f, -0.25f);
	getColliderComponent()->setOffset(glm::vec3(0.0f, -1.08f, 0.0f));
	setDrawCollider(true);
	//Physics
	addPhysicsComponent();
	getPhysicsComponent()->setGravity(glm::vec2(0.0f, -0.02f));
}

Player::~Player() {
	delete health;
}

void Player::setFacingRight(bool value) {
	isFacingRight = value;

	if (isFacingRight) {
		getTransform().setScale(glm::vec3(4.5f, -4.5f, 1.0f));
	}
	else {
		getTransform().setScale(glm::vec3(-4.5f, -4.5f, 1.0f));
	}
}

bool Player::getFacingRight() const {
	return isFacingRight;
}

void Player::setMovementSpeed(float value) {
	movementSpeed = value;
}

float Player::getMovementSpeed() const {
	return movementSpeed;
}
