#pragma once
#include "Ziz.h"



Ziz::Ziz() {
	setName("Ziz");
	health = new Health(2000);
	currentPhase = firstPhase;

	setTexture("../Resource/Ziz/Idle.png");
	getTransform().setScale(glm::vec3(10.0f, 10.0f, 1.0f));
	//Collider
	addColliderComponent();
	getColliderComponent()->setDimension(0.3f, 0.5f);
	getColliderComponent()->getTransform().translate(glm::vec3(-0.5f, 0.0f, 0.0f));
	getTransform().setPosition(glm::vec3(2.0f, 0.05, 0.0f));
	setDrawCollider(true);
	getColliderComponent()->setTrigger(true);


	//Animation
	initAnimation(10,1);
	getAnimationComponent()->addState("idle", 0, 10);
	getAnimationComponent()->addState("gust", 0, 20);
	getAnimationComponent()->addState("stormrise", 0, 57);
	getAnimationComponent()->addState("flyup",0, 7);
	getAnimationComponent()->addState("swoop", 0, 1);
	getAnimationComponent()->addState("groundslamstartup", 0, 8);
	getAnimationComponent()->addState("groundslaminair", 0, 6);
	getAnimationComponent()->addState("groundslamslamming", 0, 2);
	getAnimationComponent()->addState("groundslamrecovery", 0, 10);
	getAnimationComponent()->addState("clawslash", 0, 44);
	getAnimationComponent()->addState("wingspan", 0, 22);
	getAnimationComponent()->addState("transform", 0, 33);
	getAnimationComponent()->addState("chomp", 0, 32);

	
	//Physics
	addPhysicsComponent();
	getPhysicsComponent()->setGravity(glm::vec2(0.0f, -0.02f));
	getPhysicsComponent()->setEnableGravity(false);
	setTag(Tag::Enemy);

	//other
	isFacingRight = false;
	dead = false;
	isInvincible = false;

	currentState = new BossStateMachine();
	
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
	gust->setTexture("../Resource/Texture/Ziz/Ziz_Aircutter.png");
	
	gust->setDraw(true);
	//-1.25
	if (isFacingRight) {
		gust->getTransform().setScale(glm::vec3(-1.0f, 2.0f, 1.0f));
		gust->getTransform().setPosition(glm::vec3(getTransform().getPosition().x + 1.5f, -1.5f, 1.0f));
	}
	else {
		gust->getTransform().setScale(glm::vec3(1.0f, 2.0f, 1.0f));
		gust->getTransform().setPosition(glm::vec3(getTransform().getPosition().x - 1.5f, -1.5f, 1.0f));
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
	StormRise* stormRise = new StormRise();
	
	stormRise->setPlayer(player);
	stormRise->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x, 0.15f, 1.0f));
	
	

	return stormRise;
}

DrawableObject* Ziz::createSwoopWarning(int side) {
	SwoopWarning* warning = new SwoopWarning(side);
	return warning;
}

void Ziz::setIdleState(){
	currentState->changeState(ZizIdleState::getInstance(), this);
}

void Ziz::phaseChangeTracker() {
	if (this->health->getCurrentHP() < this->health->getRealHP()/2) {//if current health = half of realHP
		if (hasTransformed == false) {
			cout << "half Health" << endl;
			interruptPhaseChange();
			hasTransformed = true;
		}
		//currentPhase = zizPhase::secondPhase;
	}

	if (this->health->getCurrentHP() <= 0) {
		dead = true;
		interruptDeath();
		cout << "ziz is dead" << endl;
	}
}

float Ziz::getCurrentHealth() {
	return health->getCurrentHP();
}

Health* Ziz::getHealth() const {
	return health;
}

void Ziz::changePhase() {

	if (currentPhase == zizPhase::firstPhase) {
		currentPhase = zizPhase::secondPhase;
		cout << "Changed Phase to second" << endl;
	}
	else {
		currentPhase = zizPhase::firstPhase;
		cout << "Changed Phase to first" << endl;
	}
	
}

void Ziz::interruptPhaseChange() {
	getStateMachine()->interrupt(this);
}

void Ziz::interruptDeath() {
	getStateMachine()->interruptDeath(this);
}

bool Ziz::getIsInvincible() {
	return isInvincible;
}

void Ziz::setIsInvincible(bool val) {
	isInvincible = val;
}

void Ziz::startShake(float duration, float intensity) {
	isShaking = true;
	shakeDuration = duration;
	shakeTimer = 0.0f;
	shakeIntensity = intensity;
	shakeOffsetX = std::uniform_real_distribution<>(-intensity, intensity);
	shakeOffsetY = std::uniform_real_distribution<>(-intensity, intensity);
}

void Ziz::updateShake(float deltaTime) {
	if (isShaking) {
		shakeTimer += deltaTime;
		if (shakeTimer < shakeDuration) {
			GameEngine* engine = GameEngine::getInstance();
			if (engine) {
				GLRenderer* renderer = engine->getRenderer();
				if (renderer) {
					// Get the current window dimensions
					int windowWidth = engine->getWindowWidth();
					int windowHeight = engine->getWindowHeight();

					// Apply a small random offset to the viewport origin
					float offsetX = shakeOffsetX(gen) * windowWidth; // Scale by window dimensions
					float offsetY = shakeOffsetY(gen) * windowHeight;

					renderer->setViewPort(static_cast<int>(offsetX), static_cast<int>(offsetY), windowWidth, windowHeight);
				}
				else {
					std::cerr << "Error: Could not get GLRenderer in Ziz::updateShake()" << std::endl;
				}
			}
			else {
				std::cerr << "Error: Could not get GameEngine in Ziz::updateShake()" << std::endl;
			}
		}
		else {
			stopShake();
			// Reset the viewport to the original dimensions (0, 0, width, height)
			GameEngine* engine = GameEngine::getInstance();
			if (engine && engine->getRenderer()) {
				engine->getRenderer()->setViewPort(0, 0, engine->getWindowWidth(), engine->getWindowHeight());
			}
		}
	}
}

void Ziz::stopShake() {
	isShaking = false;
	shakeTimer = 0.0f;
}





void Ziz::resetCam() {
	GameEngine* engine = GameEngine::getInstance();
	if (engine) {
		GLRenderer* renderer = engine->getRenderer();
		if (renderer) {
			
			renderer->setViewPort(0.0f,0.0f, 1600.0f, 900.0f);
			
		}
		else {
			std::cerr << "Error: Could not get GLRenderer instance in handleKey." << std::endl;
		}
	}
	else {
		std::cerr << "Error: Could not get GameEngine instance in handleKey." << std::endl;
	}
}


zizPhase Ziz::getPhase() const {
	return currentPhase;
}