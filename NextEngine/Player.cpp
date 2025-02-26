#include "Player.h"
#include "Bow.h"
#include "Sword.h"
#include "Shield.h"
#include "EnemyAttackCollider.h"

Player::Player(float hp) {
	health = new Health(hp);
	setName("Player"); //--new
	setTexture("../Resource/Texture/dante_idle.png");
	getTransform().setScale(glm::vec3(4.5f, 4.5f, 1.0f));
	//Anim
	initAnimation(8, 1);
	getAnimationComponent()->addState("idle", 0, 8);
	//Collider
	addColliderComponent();
	getColliderComponent()->setDimension(0.15f, 0.25f);
	//getColliderComponent()->setOffset(glm::vec3(0.0f, -1.08f, 0.0f));
	getColliderComponent()->getTransform().translate(glm::vec3(0.0f, -1.0f, 0.0f));
	//getColliderComponent()->setTrigger(true);
	setDrawCollider(true);
	//Physics
	addPhysicsComponent();
	getPhysicsComponent()->setGravity(glm::vec2(0.0f, -0.02f));
	getPhysicsComponent()->setEnableGravity(true);
	//StateMachine
	playerState = new StateMachine();
	playerState->changeState(PlayerIdleState::getInstance(), this);
	//Bow
	bow = new Bow();
	sword = new Sword();
	shield = new Shield();
}

Player::~Player() {
	delete health;
}

void Player::setFacingRight(bool value) {
	isFacingRight = value;

	if (isFacingRight) {
		getTransform().setScale(glm::vec3(4.5f, 4.5f, 1.0f));
	}
	else {
		getTransform().setScale(glm::vec3(-4.5f, 4.5f, 1.0f));
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

void Player::setJumpPower(float value) {
	jumpingPower = value;
}

float Player::getJumpPower() const {
	return jumpingPower;
}

StateMachine* Player::getStateMachine() const {
	return playerState;
}

void Player::setWeaponType(WeaponType newType) {
	currentWeapon = newType;
}

WeaponType Player::getWeaponType() const {
	return currentWeapon;
}

void Player::setLevel(Level* newLevel) {
	if (!newLevel) {
		cerr << "Error: setLevel() received a nullptr.";
		return;
	}
	currentLevel = newLevel;
}

Level* Player::getLevel() const {
	return currentLevel;
}

Bow* Player::getBow() const{
	return bow;
}

Sword* Player::getSword() const {
	return sword;
}

Shield* Player::getShield() const {
	return shield;
}

void Player::onTriggerEnter(Collider* collider) {
	cout << "Player hit" << endl;
}