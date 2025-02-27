#pragma once
#include "Ziz.h"


Ziz::Ziz() {
	setName("Ziz");
	health = new Health(1000);

	setTexture("../Resource/Ziz/Idle.png");
	getTransform().setScale(glm::vec3(10.0f, 10.0f, 1.0f));
	//Collider
	addColliderComponent();
	getColliderComponent()->setDimension(0.5f, 0.5f);
	getTransform().setPosition(glm::vec3(2.0f, 3.0f, 0.0f));
	setDrawCollider(true);
	getColliderComponent()->setTrigger(false);
	//Animation
	//initAnimation(1, 1);
	//getAnimationComponent()->addState("idle", 0, 1);
	//Physics
	addPhysicsComponent();
	getPhysicsComponent()->setGravity(glm::vec2(0.0f, -0.02f));
	getPhysicsComponent()->setEnableGravity(true);

	//other
	isFacingRight = false;

	currentState = new BossStateMachine();
	currentState->changeState(ZizIdleState::getInstance(), this);
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
		getTransform().setScale(glm::vec3(-10.0f, 10.0f, 1.0f));
		//cout << "Ziz is Facing right" << endl;
	}
	else {
		getTransform().setScale(glm::vec3(10.0f, 10.0f, 1.0f));
		//cout << "Ziz is Facing Left" << endl;
	}
}

void Ziz::setPlayer(Player* playr) {
	player = playr;
}

bool Ziz::getFacingRight() const {
	return isFacingRight;
}

void Ziz::facePlayer() {
	if (player) {
		float playerX = player->getTransform().getPosition().x;
		float zizX = getTransform().getPosition().x;
		isFacingRight = playerX > zizX;
		setFacingRight(isFacingRight);
	}
	
}


Player* Ziz::getPlayer() {
	return player;
}

BossStateMachine* Ziz::getStateMachine() const {
	return currentState;
}

DrawableObject* Ziz::createGust() {
	
	//Create Gust
	Gust* gust = new Gust(getFacingRight());
	gust->setTexture("../Resource/Texture/Tornado.png");
	gust->getTransform().setScale(glm::vec3(2.5f, 2.5f, 1.0f));
	gust->setDraw(true);
	//-1.25
	if (isFacingRight) {
		gust->getTransform().setPosition(glm::vec3(getTransform().getPosition().x + 1.5f, -1.2f, 1.0f));
	}
	else {
		gust->getTransform().setPosition(glm::vec3(getTransform().getPosition().x - 1.5f, -1.2f, 1.0f));
	}
	

	gust->addColliderComponent();
	gust->getColliderComponent()->setTrigger(false);
	gust->getColliderComponent()->setDimension(0.5f, 1.0f);
	gust->setDrawCollider(true);
	gust->addPhysicsComponent();
	gust->getPhysicsComponent()->setGravity(glm::vec2(0.0f, -0.02f));
	gust->getPhysicsComponent()->setEnableGravity(true);
	
	
	return gust;
}


DrawableObject* Ziz::createStormRise() {
	StormRise* stormRise = new StormRise(3.0f);
	stormRise->setTexture("../Resource/Ziz/StormRiseProjectile.png");
	stormRise->getTransform().setScale(glm::vec3(2.5f, 2.5f, 1.0f));
	stormRise->setDraw(true);
	stormRise->getTransform().setPosition(glm::vec3(getTransform().getPosition().x,-2.4f,1.0f));

	stormRise->addColliderComponent();
	stormRise->getColliderComponent()->setTrigger(false);
	stormRise->getColliderComponent()->setDimension(0.5f, 0.15f);
	stormRise->getColliderComponent()->getTransform().translate(glm::vec3(0.0f, 0.1f, 0.0f));
	stormRise->setDrawCollider(true);
	stormRise->addPhysicsComponent();
	stormRise->getPhysicsComponent()->setGravity(glm::vec2(0.0f, -0.1f));
	stormRise->getPhysicsComponent()->setEnableGravity(true);
	stormRise->setPlayer(player);

	return stormRise;
}
