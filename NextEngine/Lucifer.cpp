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
	//setDrawCollider(true);
	//setCanDrawColliderNew(true);
	getColliderComponent()->setTrigger(true);
	setTag(Tag::Enemy);

	instance = this;
	isInvincible = false;

	qteInputReceieved = false;
	qteMode = false;
	qteInputReceieved = false;
	QTETarget = 0;
	QTEInput = 0;
	QTECorrect = false;

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

IceSpear* Lucifer::createIceSpear(FacingDirection fd) {
	IceSpear* iceSpear = new IceSpear(fd);
	return iceSpear;
}

void Lucifer::startShake(float duration, float intensity) {
	isShaking = true;
	shakeDuration = duration;
	shakeTimer = 0.0f;
	shakeIntensity = intensity;
	shakeOffsetX = std::uniform_real_distribution<>(-intensity, intensity);
	shakeOffsetY = std::uniform_real_distribution<>(-intensity, intensity);
	
}

void Lucifer::updateShake(float deltaTime) {
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

void Lucifer::stopShake() {
	isShaking = false;
	shakeTimer = 0.0f;
}





void Lucifer::resetCam() {
	GameEngine* engine = GameEngine::getInstance();
	if (engine) {
		GLRenderer* renderer = engine->getRenderer();
		if (renderer) {

			renderer->setViewPort(0.0f, 0.0f, 1600.0f, 900.0f);

		}
		else {
			std::cerr << "Error: Could not get GLRenderer instance in handleKey." << std::endl;
		}
	}
	else {
		std::cerr << "Error: Could not get GameEngine instance in handleKey." << std::endl;
	}
}

QTEButtonUI* Lucifer::createQTEButtonUI() {
	QTEButtonUI* qteButtonUI = new QTEButtonUI(QTETarget);
	qteButtonUI->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x, 0, 0));
	return qteButtonUI;
}

void Lucifer::updateQTEMode(float dt) {

}

void Lucifer::handleQTEInput(int input) {



	QTEInput = input;
	//cout << "ziz receieved qte input: " << input << endl;
	QTECorrect = (QTEInput == QTETarget);
	if (QTECorrect == true) {
		startShake(0.05f, 0.0015f);
	}
	qteInputReceieved = true;
}

void Lucifer::startQTEMode(int target) {
	SoundManager::GetInstance()->PlaySFX("Dante-QTE_Parry");
	qteInputReceieved = false;
	QTETarget = target;
	QTECorrect = false;
	//cout << "QTE Mode Started, target: " << target << endl;
	qteMode = true;
}

void Lucifer::endQTEMode() {
	QTECorrect = false;
	qteMode = false;
	//cout << "end qte mode" << endl;
}

bool Lucifer::getQTECorrect() {
	return QTECorrect;
}

bool Lucifer::getQTEMode() {
	return qteMode;
}

bool Lucifer::getQTEInputReceieved() {
	return qteInputReceieved;
}