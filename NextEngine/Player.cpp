#include "Player.h"
#include "Bow.h"
#include "Sword.h"
#include "Shield.h"
#include "EnemyAttackCollider.h"
#include "GameEngine.h"

Player::Player(float currentHealth, float witherHealth, int life) {
	health = new Health(currentHealth, witherHealth);
	playerLives = life;
	setName("Player"); //--new
	setTag(Tag::Player);

	//texturePaths = { //vector holding paths (might create something that automatically load files into map for easier use)
	//	//Sword
	//	"../Resource/Texture/Dante/DanteSword/dante_idle_sword.png", //path
	//	"../Resource/Texture/Dante/DanteSword/dante_walking_sword.png",
	//	"../Resource/Texture/Dante/DanteSword/dante_jumping_sword.png",
	//	"../Resource/Texture/Dante/DanteSword/dante_dash_sword.png",
	//	"../Resource/Texture/Dante/DanteSword/dante_lightAttack1_sword.png",
	//	"../Resource/Texture/Dante/DanteSword/dante_lightAttack2_sword.png",
	//	"../Resource/Texture/Dante/DanteSword/dante_lightAttack3_sword.png",
	//	"../Resource/Texture/Dante/DanteSword/dante_heavyAttack_sword.png",
	//	"../Resource/Texture/Dante/DanteSword/dante_smallUlt_sword.png",
	//	//Shield
	//	"../Resource/Texture/Dante/DanteShield/dante_idle_shield.png", //path
	//	"../Resource/Texture/Dante/DanteShield/dante_walking_shield.png",
	//	"../Resource/Texture/Dante/DanteShield/dante_jumping_shield.png",
	//	"../Resource/Texture/Dante/DanteShield/dante_falling_shield.png",
	//	"../Resource/Texture/Dante/DanteShield/dante_dash_shield.png",
	//	"../Resource/Texture/Dante/DanteShield/dante_lightAttack1_shield.png",
	//	"../Resource/Texture/Dante/DanteShield/dante_lightAttack2_shield.png",
	//	"../Resource/Texture/Dante/DanteShield/dante_holding_shield.png",
	//	"../Resource/Texture/Dante/DanteShield/dante_off_shield.png",
	//	"../Resource/Texture/Dante/DanteShield/dante_smallUlt_shield.png",
	//	"../Resource/Texture/Dante/DanteShield/dante_bigUlt_shield.png",
	//	//Bow
	//	"../Resource/Texture/Dante/DanteBow/dante_idle_bow.png", //path
	//	"../Resource/Texture/Dante/DanteBow/dante_walking_bow.png",
	//	"../Resource/Texture/Dante/DanteBow/dante_jumping_bow.png",
	//	"../Resource/Texture/Dante/DanteBow/dante_falling_bow.png",
	//	"../Resource/Texture/Dante/DanteBow/dante_dash_bow.png",
	//	"../Resource/Texture/Dante/DanteBow/dante_lightAttack_bow.png",
	//	"../Resource/Texture/Dante/DanteBow/dante_heavyAttack_bow.png",
	//	"../Resource/Texture/Dante/DanteBow/dante_smallUlt_bow.png",
	//	"../Resource/Texture/Dante/DanteBow/dante_bigUlt_bow.png",
	//};

	//GameEngine::getInstance()->getRenderer()->preloadTextures(texturePaths); //preload all paths

	setTexture("../Resource/Texture/Dante/DanteSword/dante_idle_sword.png");
	getTransform().setScale(glm::vec3(4.5f, 4.5f, 1.0f));
	//Anim
	initAnimation(8, 1);
	//Sword States
	getAnimationComponent()->addState("idleSword", 0, 8); 
	getAnimationComponent()->addState("walkingSword", 0, 8);
	getAnimationComponent()->addState("jumpingSword", 0, 1);
	getAnimationComponent()->addState("fallingSword", 0, 1);
	getAnimationComponent()->addState("dashSword", 0, 1);
	getAnimationComponent()->addState("lightAttack1Sword", 0, 6);
	getAnimationComponent()->addState("lightAttack2Sword", 0, 5);
	getAnimationComponent()->addState("lightAttack3Sword", 0, 5);
	getAnimationComponent()->addState("heavyAttackSword", 0, 7);
	getAnimationComponent()->addState("smallUltSword", 0, 10);
	getAnimationComponent()->addState("bigUltSword", 0, 25);
	//Shield States
	getAnimationComponent()->addState("idleShield", 0, 8);
	getAnimationComponent()->addState("walkingShield", 0, 8);
	getAnimationComponent()->addState("jumpingShield", 0, 1);
	getAnimationComponent()->addState("fallingShield", 0, 1);
	getAnimationComponent()->addState("dashShield", 0, 1);
	getAnimationComponent()->addState("lightAttack1Shield", 0, 16);
	getAnimationComponent()->addState("lightAttack2Shield", 0, 11);
	getAnimationComponent()->addState("holdShield", 0, 2);
	getAnimationComponent()->addState("offShield", 0, 3);
	getAnimationComponent()->addState("smallUltShield", 0, 11);
	getAnimationComponent()->addState("bigUltShield", 0, 23);
	//Bow States
	getAnimationComponent()->addState("idleBow", 0, 8);
	getAnimationComponent()->addState("walkingBow", 0, 8);
	getAnimationComponent()->addState("jumpingBow", 0, 1);
	getAnimationComponent()->addState("fallingBow", 0, 1);
	getAnimationComponent()->addState("dashBow", 0, 1);
	getAnimationComponent()->addState("lightAttackBow", 0, 8);
	getAnimationComponent()->addState("heavyAttackBow", 0, 16);
	getAnimationComponent()->addState("smallUltBow", 0, 17);
	getAnimationComponent()->addState("bigUltBow", 0, 18);
	//Death
	getAnimationComponent()->addState("death", 0, 1);

	//Collider
	addColliderComponent();
	getColliderComponent()->setDimension(0.15f, 0.25f);
	//getColliderComponent()->setOffset(glm::vec3(0.0f, -1.08f, 0.0f));
	getColliderComponent()->getTransform().translate(glm::vec3(0.0f, -1.0f, 0.0f));
	//getColliderComponent()->setTrigger(true);
	//setDrawCollider(true);
	//Physics
	addPhysicsComponent();
	getPhysicsComponent()->setGravity(glm::vec2(0.0f, -20.0f));
	getPhysicsComponent()->setEnableGravity(true);
	//StateMachine
	playerState = new StateMachine();
	playerState->changeState(PlayerIdleState::getInstance(), this);
	//Bow
	bow = new Bow();
	sword = new Sword();
	shield = new Shield();
	//GroundChecker
	groundChecker = new GroundChecker();
	groundChecker->setPlayer(this);
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

GroundChecker* Player::getGroundChecker() const {
	return groundChecker;
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

Health* Player::getHealth() const {
	return health;
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

//void Player::onCollisionEnter(Collider* collider) {
//	DrawableObject* obj = collider->getObject();
//
//	if (obj->getName() == "Floor") {
//		cout << "player hit the floor" << endl;
//	}
//
//	cout << "player hit the floor" << endl;
//}
//
//void Player::onCollisionStay(Collider* collider) {
//	DrawableObject* obj = collider->getObject();
//
//	if (obj->getName() == "Floor") {
//		cout << "player hit the floor" << endl;
//	}
//
//	cout << "player hit the floor" << endl;
//}
//
//void Player::onTriggerEnter(Collider* collider) {
//	DrawableObject* obj = collider->getObject();
//
//	if (obj->getName() == "Floor") {
//		cout << "player hit the floor" << endl;
//	}
//
//	cout << "player hit the floor" << endl;
//}
//
//void Player::onTriggerStay(Collider* collider) {
//	DrawableObject* obj = collider->getObject();
//
//	if (obj->getName() == "Floor") {
//		cout << "player hit the floor" << endl;
//	}
//
//	cout << "player hit the floor" << endl;
//}