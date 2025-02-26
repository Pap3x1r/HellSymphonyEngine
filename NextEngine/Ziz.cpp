#include "Ziz.h"
#include "Player.h"


Ziz::Ziz() {
	setName("Ziz");
	health = new Health(1000);
	setTexture("../Resource/Ziz/Idle.png");
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
	isFacingRight = false;

	currentState = new BossStateMachine();
	currentState->changeState(ZizIdleState::getInstance(), this);
}

Ziz::~Ziz() {
	delete health;
	delete currentLevel;
	delete currentState;
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

void Ziz::setPlayer(Player* playr) {
	player = playr;
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
	gust->getTransform().setPosition(getTransform().getPosition());

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
	stormRise->getTransform().setPosition(getTransform().getPosition());

	stormRise->addColliderComponent();
	stormRise->getColliderComponent()->setTrigger(false);
	stormRise->getColliderComponent()->setDimension(0.5f, 0.15f);
	stormRise->getColliderComponent()->getTransform().translate(glm::vec3(0.0f, 0.1f, 0.0f));
	stormRise->setDrawCollider(true);
	stormRise->addPhysicsComponent();
	stormRise->getPhysicsComponent()->setGravity(glm::vec2(0.0f, -0.02f));
	stormRise->getPhysicsComponent()->setEnableGravity(true);
	stormRise->setPlayer(player);

	return stormRise;
}
