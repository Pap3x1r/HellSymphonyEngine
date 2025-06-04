#include "Lucifer.h"

Lucifer* Lucifer::instance = nullptr;

Lucifer* Lucifer::getInstance() {
	if (!instance) {
		instance = new Lucifer();
	}
	return instance;
}

Lucifer::Lucifer() {
	setName("Lucifer");
	health = new Health(7500, 0, 7500);
	setTexture("../Resource/Texture/Lucifer/LuciferPhase1.png");
	getTransform().setScale(glm::vec3(20.0f, 10.0f, 1.0f));
	getTransform().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	//Collider
	addColliderComponent();
	getColliderComponent()->setDimension(0.1f, 0.3f);
	getColliderComponent()->getTransform().setPosition(glm::vec3(0,-1,0));
	setDrawCollider(true);
	setCanDrawColliderNew(true);
	getColliderComponent()->setTrigger(true);
	setTag(Tag::Enemy);

	instance = this;
	isInvincible = false;

	currentState = new BossStateMachine();
	currentState->changeState(LuciferIdleState::getInstance(), this);

}

Lucifer::~Lucifer() {
	delete health;
}

void Lucifer::setLevel(Level* newLevel) {
	currentLevel = newLevel;
}

Level* Lucifer::getLevel() const {
	return currentLevel;
}

void Lucifer::setFacingRight(bool value) {
	
}

void Lucifer::update(float dt) {

}


BossStateMachine* Lucifer::getStateMachine() const {
	return currentState;
}

void Lucifer::setPlayer(Player* playr) {
	player = playr;
}

Player* Lucifer::getPlayer(){
	return player;
}

Health* Lucifer::getHealth() const {
	return health;
}

bool Lucifer::getIsInvincible() {
	return isInvincible;
}

void Lucifer::setIsInvincible(bool val) {
	isInvincible = val;
}