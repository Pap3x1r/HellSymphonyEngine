#pragma once
#include "Ziz.h"
#include "ZizIntroState.h"

Ziz* Ziz::instance = nullptr;

Ziz* Ziz::getInstance() {
	if (!instance) {
		//cout << "ziz created singleton" << endl;
		instance = new Ziz();
	}
	return instance;
}

Ziz::Ziz() {
	setName("Ziz");
	health = new Health(10000, 0, 10000);
	currentPhase = firstPhase;

	//GameEngine::getInstance()->getRenderer()->loadTextureFromDir("../Resource/Texture/Ziz");
	//GameEngine::getInstance()->getRenderer()->loadTextureFromDir("../Resource/Texture/FinalZiz");

	setTexture("../Resource/Ziz/Idle.png");
	getTransform().setScale(glm::vec3(10.0f, 10.0f, 1.0f));
	//Collider
	addColliderComponent();
	getColliderComponent()->setDimension(0.3f, 0.5f);
	//getColliderComponent()->getTransform().translate(glm::vec3(-0.5f, 0.0f, 0.0f));
	getTransform().setPosition(glm::vec3(2.0f, -0.25f, 0.0f));
	setDrawCollider(true);
	//setCanDrawColliderNew(true);
	getColliderComponent()->setTrigger(true);


	//Animation
	initAnimation(10,1);
	getAnimationComponent()->addState("idle", 0, 10);
	getAnimationComponent()->addState("gust", 0, 20);

	//swoop
	getAnimationComponent()->addState("flyup",0, 7);
	getAnimationComponent()->addState("swoop", 0, 1);
	getAnimationComponent()->addState("swooprecovery", 0, 16);

	//wingspan
	getAnimationComponent()->addState("wingspan", 0, 22);

	//clawslash
	getAnimationComponent()->addState("clawslashstartup1", 0, 16);
	getAnimationComponent()->addState("clawslashactive1", 0, 4);
	getAnimationComponent()->addState("clawslashstartup2", 0, 2);
	getAnimationComponent()->addState("clawslashactive2", 0, 3);
	getAnimationComponent()->addState("clawslashstartup3", 0, 4);
	getAnimationComponent()->addState("clawslashactive3", 0, 6);
	getAnimationComponent()->addState("clawslashrecovery", 0, 9);

	//groundslam
	getAnimationComponent()->addState("groundslam", 0, 24);
	getAnimationComponent()->addState("groundslamstartup", 0, 14);
	getAnimationComponent()->addState("groundslamactive", 0, 5);
	getAnimationComponent()->addState("groundslamrecovery", 0, 5);

	//stormrise
	getAnimationComponent()->addState("stormrisestartup1", 0, 8);
	getAnimationComponent()->addState("stormrisestartup2", 0, 16);
	getAnimationComponent()->addState("stormriseactive", 0, 2);
	getAnimationComponent()->addState("stormriserecovery1", 0, 15);
	getAnimationComponent()->addState("stormriserecovery2", 0, 6);
	getAnimationComponent()->addState("stormriserecovery3", 0, 10);

	//transform
	getAnimationComponent()->addState("transform", 0, 33);

	//chomp
	getAnimationComponent()->addState("chomp", 0, 32);

	//QTE;
	getAnimationComponent()->addState("qtestart1", 0, 8);
	getAnimationComponent()->addState("qtestart2", 0, 16);
	getAnimationComponent()->addState("qterecovery", 0, 10);


	
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
	instance = this;

	//cout << "ziz created" << endl;
	qteInputReceieved = false;
	qteMode = false;
	qteInputReceieved = false;
	QTETarget = 0;
	QTEInput = 0;
	QTECorrect = false;

	currentState->changeState(ZizIdleState::getInstance(), this);
	//currentState->changeState(ZizIntroState::getInstance(), this);
	
}

Ziz::~Ziz() {
	delete health;

}

void Ziz::update(float dt) {
	(distanceFromPlayer = abs(getTransform().getPosition().x - getPlayer()->getTransform().getPosition().x));
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
		getTransform().setScale(glm::vec3(-10.0f, getTransform().getScale().y, getTransform().getScale().z));
		//cout << "Ziz is Facing right" << endl;
	}
	else {
		getTransform().setScale(glm::vec3(10.0f, getTransform().getScale().y, getTransform().getScale().z));
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
		if (isFacingRight) {
			Transform defaultTransform;
			//defaultTransform.setPosition();
			getColliderComponent()->getTransform().setPosition(glm::vec3(0.5f, 0.0f, 0.0f));
		}
		else {
			getColliderComponent()->getTransform().setPosition(glm::vec3(-0.5f, 0.0f, 0.0f));
		}
		
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
		gust->getTransform().setScale(glm::vec3(-1.0f, 4.0f, 1.0f));
		gust->getTransform().setPosition(glm::vec3(getTransform().getPosition().x + 1.5f, -1.5f, 1.0f));
	}
	else {
		gust->getTransform().setScale(glm::vec3(1.0f, 4.0f, 1.0f));
		gust->getTransform().setPosition(glm::vec3(getTransform().getPosition().x - 1.5f, -1.5f, 1.0f));
	}
	

	gust->addColliderComponent();
	gust->getColliderComponent()->setTrigger(true);
	gust->getColliderComponent()->setDimension(0.5f, 1.0f);
	
	return gust;
	
}


DrawableObject* Ziz::createStormRise() {
	StormRise* stormRise = new StormRise();
	
	stormRise->setPlayer(player);
	stormRise->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x, 0.15f, 1.0f));
	
	//cout << "Ziz Created Stormrise" << endl;
	return stormRise;

}

DrawableObject* Ziz::createSwoopWarning(int side) {
	SwoopWarning* warning = new SwoopWarning(side);
	return warning;
}

QTEButtonUI* Ziz::createQTEButtonUI(){
	QTEButtonUI* qteButtonUI = new QTEButtonUI(QTETarget);
	qteButtonUI->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x, 0, 0));
	return qteButtonUI;
}

DrawableObject* Ziz::createBGZiz() {
	UltZizOnBG* ultZizOnBG = new UltZizOnBG(this);
	//cout << "creat bg from ziz" << endl;

	return ultZizOnBG;
}

DrawableObject* Ziz::createChompTentacle() {
	ChompTentacle* chompTentacle = new ChompTentacle(isFacingRight,this);
	
	if (isFacingRight) {
		chompTentacle->getTransform().setPosition(glm::vec3(getTransform().getPosition().x + 3.0f, getTransform().getPosition().y - 0.15f, 1.0f));
	}
	else {
		chompTentacle->getTransform().setPosition(glm::vec3(getTransform().getPosition().x - 3.0f, getTransform().getPosition().y - 0.15f, 1.0f));
	}
	return chompTentacle;

}

DrawableObject* Ziz::createLightning() {
	Lightning* lightning = new Lightning(this);
	return lightning;
}

DrawableObject* Ziz::createLightning(float x) {
	Lightning* lightning = new Lightning(this, x);
	return lightning;
}

DrawableObject* Ziz::createImpale() {
	Impale* impale = new Impale(this);
	return impale;
}

void Ziz::setIdleState(){
	currentState->changeState(ZizIdleState::getInstance(), this);
}

void Ziz::phaseChangeTracker() {
	if (this->health->getCurrentHP() < this->health->getRealHP()/2) {//if current health = half of realHP
		if (hasTransformed == false) {
			//cout << "half Health" << endl;
			interruptPhaseChange();
			hasTransformed = true;
			SoundManager::GetInstance()->StopAllSounds();
			SoundManager::GetInstance()->PlayMusic("Ziz_Gluttony-Soundtrack");
		}
		//currentPhase = zizPhase::secondPhase;
	}

	if (this->health->getCurrentHP() <= 0) {
		dead = true;
		interruptDeath();
		//cout << "ziz is dead" << endl;
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
		//cout << "Changed Phase to second" << endl;
	}
	else {
		currentPhase = zizPhase::firstPhase;
		//cout << "Changed Phase to first" << endl;
	}
	
}

void Ziz::interruptPhaseChange() {
	getStateMachine()->interruptPhaseChange(this);
}

void Ziz::interruptDeath() {
	getStateMachine()->interruptDeath(this);
}

void Ziz::interruptIntoPhase() {
	getStateMachine()->interruptIntoPhase(this);
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

void Ziz::updateQTEMode(float dt) {
	
}

void Ziz::handleQTEInput(int input) {



	QTEInput = input;
	//cout << "ziz receieved qte input: " << input << endl;
	QTECorrect = (QTEInput == QTETarget);
	if (QTECorrect == true) {
		startShake(0.05f, 0.0015f);
	}
	qteInputReceieved = true;
}

void Ziz::startQTEMode(int target) {
	SoundManager::GetInstance()->PlaySFX("Dante-QTE_Parry");
	qteInputReceieved = false;
	QTETarget = target;
	QTECorrect = false;
	//cout << "QTE Mode Started, target: " << target << endl;
	qteMode = true;
}

void Ziz::endQTEMode() {
	QTECorrect = false;
	qteMode = false;
	//cout << "end qte mode" << endl;
}

bool Ziz::getQTECorrect() {
	return QTECorrect;
}

bool Ziz::getQTEMode() {
	return qteMode;
}

bool Ziz::getQTEInputReceieved() {
	return qteInputReceieved;
}

float Ziz::getDistanceFromPlayer() {
	return distanceFromPlayer;
}


zizPhase Ziz::getCurrentPhase() const {
	return currentPhase;
}

