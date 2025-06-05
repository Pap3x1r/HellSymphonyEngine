#include "Player.h"
#include "Bow.h"
#include "Sword.h"
#include "Shield.h"
#include "EnemyAttackCollider.h"
#include "GameEngine.h"

Player::Player(float currentHealth, float witherHealth, int life) {
	health = new Health(currentHealth, witherHealth, 100.0f);
	playerLives = life;
	setName("Player"); //--new
	setTag(Tag::Player);

	setTexture("../Resource/Texture/Dante/DanteSword/dante_idle_sword.png");
	getTransform().setScale(glm::vec3(3.75f, 3.75f, 1.0f));
	//Anim
	initAnimation(8, 1);
	//None States
	getAnimationComponent()->addState("idleNone", 0, 8);
	getAnimationComponent()->addState("walkingNone", 0, 8);
	getAnimationComponent()->addState("jumpingNone", 0, 1);
	getAnimationComponent()->addState("fallingNone", 0, 1);
	getAnimationComponent()->addState("dashNone", 0, 1);

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
	getAnimationComponent()->addState("holdShield", 0, 3);
	getAnimationComponent()->addState("offShield", 0, 3);
	getAnimationComponent()->addState("smallUltShield", 0, 11);
	getAnimationComponent()->addState("bigUltShield", 0, 24);
	//Bow States
	getAnimationComponent()->addState("idleBow", 0, 8);
	getAnimationComponent()->addState("walkingBow", 0, 8);
	getAnimationComponent()->addState("jumpingBow", 0, 1);
	getAnimationComponent()->addState("fallingBow", 0, 1);
	getAnimationComponent()->addState("dashBow", 0, 1);
	getAnimationComponent()->addState("lightAttackBow", 0, 7);
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
	setDrawCollider(true);
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

void Player::selfUpdate(float dt_) {
	if (isDead) return;

	static float time;
	time += dt_;

	if (isInvincible) {
		invincibleTimer -= dt_;

		if (invincibleTimer <= 0) {
			invincibleTimer = 0;
			isInvincible = false;
		}
	}

	if (currentUltimateSlot < ultimateSlotMax) {
		if (currentUltimateGauge >= ultimateGaugeMax) {
			increaseUltimateSlot(1);
			currentUltimateGauge -= ultimateGaugeMax;
			cout << "Ultimate Slot is increased by 1, the current is: " << currentUltimateSlot << endl;
		}
	}
	else {
		//cout << "Ultimate Slot is maxed" << endl;
		if (currentUltimateGauge > 0.0f) {
			setUltimateGauge(0.0f); //Prevent excess gauge when ultimate slot is maxed
		}

		if (currentUltimateSlot > ultimateSlotMax) {
			currentUltimateSlot = ultimateSlotMax;
		}
	}

	if (isDashing) {
		if (isFacingRight) {
			getPhysicsComponent()->setVelocity(glm::vec2(movementSpeed, 0.0f));
		}
		else {
			getPhysicsComponent()->setVelocity(glm::vec2(-movementSpeed, 0.0f));
		}

		if (movementSpeed > minMovementSpeed) {
			movementSpeed -= 80 * dt_;
		}

		if (movementSpeed <= minMovementSpeed) {
			movementSpeed = minMovementSpeed;
			isDashing = false;
			dashTimer = 0.0f;
		}

		//cout << "Player movement speed: " << movementSpeed << endl;
	}
	else {
		dashTimer += dt_;
		if (dashTimer >= dashCooldown) {
			canDash = true;
		}
	}

	if (isGrounded == false && !isDashing) {
		if (getPhysicsComponent()->getVelocity().y > velocityThreshold) {
			getStateMachine()->changeState(PlayerJumpUpState::getInstance(), this);
		}
		else if (getPhysicsComponent()->getVelocity().y < -velocityThreshold) {
			getStateMachine()->changeState(PlayerFallDownState::getInstance(), this);
		}
	}

	if (isStunned == true) {
		
		if (stunTimer > 0) {
			stunTimer -= dt_;
			cout << "stunTimer: " << stunTimer << endl;
			getPhysicsComponent()->setVelocity(glm::vec2(0.0f, getPhysicsComponent()->getVelocity().y));
			if (stunTimer <= 0) {
				isStunned = false;
				getPhysicsComponent()->setVelocity(glm::vec2(0.0f, getPhysicsComponent()->getVelocity().y));
				stunTimer = 0.0f;
			}
		}
	}


	//Set groundChecker position
	groundChecker->getTransform().setPosition(glm::vec3(getTransform().getPosition().x, getTransform().getPosition().y - 1.6f, getTransform().getPosition().z));
	//groundChecker->getTransform().setPosition(glm::vec3(getTransform().getPosition().x, getTransform().getPosition().y - 2.0f, getTransform().getPosition().z)); //test pos

	//cout << "Player position x: " << getTransform().getPosition().x << " y: " << getTransform().getPosition().y << endl;

	//cout << "Player (x,y) velocity: (" << getPhysicsComponent()->getVelocity().x << " , " << getPhysicsComponent()->getVelocity().y << ")" << endl;


	//cout << getNewColor().x << "," << getNewColor().y << "," << getNewColor().z << "," << getNewColor().a << endl;

	if (time >= 1.50f) {
		time = 0.0f;
		//cout << "Current Ultimate Gauge: " << currentUltimateGauge << endl;
		//cout << "Player ultimate slot: " << currentUltimateSlot << endl;
	}

	const char* weaponNames[] = { "None", "Sword", "Bow", "Shield" };

	int weaponIndex = static_cast<int>(currentWeapon);

	//if (ImGui::TreeNode("Player Object")) {
	//	//Health
	//	if (ImGui::TreeNode("Health")) {
	//		ImGui::SliderFloat("Current Health:", health->getCurrentHPAddress(), 0, health->getMaxHP());
	//		ImGui::TreePop();
	//	}

	//	//Ultimate
	//	if (ImGui::TreeNode("Ultimate")) {
	//		ImGui::SliderFloat("Ultimate Gauge:", &currentUltimateGauge, 0, ultimateGaugeMax);
	//		ImGui::SliderInt("Ultimate Slot:", &currentUltimateSlot, 0, ultimateSlotMax);
	//		ImGui::TreePop();
	//	}

	//	//General
	//	if (ImGui::TreeNode("General")) {
	//		ImGui::Text("Player Position; x:%.2f, y:%.2f", getTransform().getPosition().x, getTransform().getPosition().y);
	//		ImGui::Checkbox("Can Jump", &isGrounded);
	//		ImGui::Checkbox("Can Dash", &canDash);
	//		if (ImGui::Combo("Weapon Type", &weaponIndex, weaponNames, IM_ARRAYSIZE(weaponNames))) {
	//			currentWeapon = static_cast<WeaponType>(weaponIndex);
	//		}
	//		ImGui::TreePop();
	//	}

	//	if (ImGui::TreeNode("Collider")) {
	//		ImGui::Checkbox("Player Collider", getCanDrawColliderAddress());
	//		ImGui::Checkbox("Ground Checker Collider", groundChecker->getCanDrawColliderAddress());
	//		ImGui::Checkbox("Sword Collider", sword->getCanDrawColliderAddress());
	//		ImGui::Checkbox("Shield Collider", shield->getCanDrawColliderAddress());
	//		ImGui::TreePop();
	//	}

	//	ImGui::TreePop();
	//}

}

void Player::setFacingRight(bool value) {
	isFacingRight = value;

	if (isFacingRight) {
		getTransform().setScale(glm::vec3(3.75f, 3.75f, 1.0f));
	}
	else {
		getTransform().setScale(glm::vec3(-3.75f, 3.75f, 1.0f));
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

void Player::startShake(float duration, float intensity) {
	//cout << "Player Start Shake" << endl;
	isShaking = true;
	shakeDuration = duration;
	shakeTimer = 0.0f;
	shakeIntensity = intensity;
	shakeOffsetX = std::uniform_real_distribution<>(-intensity, intensity);
	shakeOffsetY = std::uniform_real_distribution<>(-intensity, intensity);
}

void Player::updateShake(float deltaTime) {
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

void Player::stopShake() {
	isShaking = false;
	shakeTimer = 0.0f;
}

void Player::stun(float duration) {
	if (isStunned == false) {
		isStunned = true;
		stunTimer = duration;
		//cout << "stunned for: " << duration << " second(s)" << endl;
	}
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