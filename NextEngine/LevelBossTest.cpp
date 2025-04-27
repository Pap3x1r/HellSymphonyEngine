#include "LevelBossTest.h"
#include "CollisionHandler.h"
#include "Bow.h"
#include "ZizGroundSlamState.h"
#include "GameEngine.h" // Include GameEngine header
#include "GLRenderer.h" // Include GLRenderer header
#include <iostream>
#include <random>
using namespace std;




void LevelBossTest::levelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->loadData();
	GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

	SquareBorderMesh* border = new SquareBorderMesh();
	border->loadData();
	GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);

	//cout << "Load Level" << endl;
}

void LevelBossTest::levelInit() {

	TexturedObject* background = new TexturedObject("background");
	background->setTexture("../Resource/Texture/Lust_Alpha.png");
	background->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	objectsList.push_back(background);
	

	Player* player_ = new Player(100, 0, 3);
	objectsList.push_back(player_);
	player = player_;
	player->setLevel(this);
	player->getTransform().setPosition(glm::vec3(-5.0,-0.8f,0.0f));
	objectsList.push_back(player->getGroundChecker());

	player->setWeaponType(Sword_);
	player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);

	playerTimeScale = 1.0f;

	if (player->getBow()) {
		for (DrawableObject* obj : player->getBow()->getChainAttackList()) {
			BowUltimateCollider* col = dynamic_cast<BowUltimateCollider*>(obj);
			col->setPlayer(player);
			objectsList.push_back(obj);
		}
	}

	if (player->getSword()) {
		for (DrawableObject* obj : player->getSword()->getChainAttackList()) {
			PlayerAttackCollider* col = dynamic_cast<PlayerAttackCollider*>(obj);
			col->setPlayer(player);
			objectsList.push_back(obj);
		}
	}

	if (player->getShield()) {
		for (DrawableObject* obj : player->getShield()->getChainAttackList()) {
			PlayerAttackCollider* col = dynamic_cast<PlayerAttackCollider*>(obj);
			col->setPlayer(player);
			objectsList.push_back(obj);
		}
	}


	Ziz* ziz_ = new Ziz();
	objectsList.push_back(ziz_);
	ziz = ziz_;
	ziz->setLevel(this);
	ziz->setPlayer(player);
	ziz->setIdleState();


	/*Gust* gust_ = new Gust();
	objectsList.push_back(gust_);
	gust = gust_;
	gust->getTransform().setPosition(glm::vec3(0.0f, -2.0f, 0.0f));*/

	/*StormRise* stormRise_ = new StormRise();
	objectsList.push_back(stormRise_);
	stormRise = stormRise_;
	stormRise->getTransform().setPosition(glm::vec3(0.0f,-2.0f,0.0f));
	stormRise->setPlayer(player);*/


	/*SwoopWarning* warning = new SwoopWarning();
	objectsList.push_back(warning);*/

	/*ChompTentacle* chompTentacle_ = new ChompTentacle();
	objectsList.push_back(chompTentacle_);
	chompTentacle = chompTentacle_;*/

	SimpleObject* floor = new SimpleObject();
	floor->getTransform().setPosition(glm::vec3(0.0f, -3.7f, 0.0f));
	floor->getTransform().setScale(glm::vec3(18.0f, 2.0f, 0.0f));
	floor->addColliderComponent();
	floor->setName("Floor");
	//floor->setDrawCollider(true);
	floor->setDraw(false);
	objectsList.push_back(floor);


	//cout << "Init Level" << endl;

	SimpleObject* witherHealthBar_ = new SimpleObject();
	witherHealthBar_->setColor(106.0f / 255.0f, 109.0f / 255.0f, 115.0f / 255.0f);
	witherHealthBar_->getTransform().setScale(glm::vec3(4.5f, 0.45f, 0.0f));
	witherHealthBar_->getTransform().setPosition(glm::vec3(-4.0f, -4.0f, 0.0f));
	objectsList.push_back(witherHealthBar_);
	witherHealthBar = witherHealthBar_;

	SimpleObject* healthBar = new SimpleObject();
	healthBar->setColor(0.0f, 1.0f, 0.0f);
	healthBar->getTransform().setScale(glm::vec3(4.5f, 0.45f, 0.0f));
	healthBar->getTransform().setPosition(glm::vec3(-4.0f, -4.0f, 0.0f));
	objectsList.push_back(healthBar);
	playerHealthBar = healthBar;

	SimpleObject* ultimateBar = new SimpleObject();
	ultimateBar->setColor(235.0f / 255.0f, 168.0f / 255.0f, 52.0f / 255.0f);
	ultimateBar->getTransform().setScale(glm::vec3(2.5f, 0.18f, 0.0f));
	ultimateBar->getTransform().setPosition(glm::vec3(-4.0f, -3.65f, 0.0f));
	objectsList.push_back(ultimateBar);
	playerUltimateBar = ultimateBar;

	SimpleObject* bossHealthBar_ = new SimpleObject();
	bossHealthBar_->setColor(0.0f, 1.0f, 0.0f);
	bossHealthBar_->getTransform().setScale(glm::vec3(9.0f, 0.25f, 0.0f));
	bossHealthBar_->getTransform().setPosition(glm::vec3(0.0f, 4.0f, 0.0f));
	objectsList.push_back(bossHealthBar_);
	bossHealthBar = bossHealthBar_;
	


}

void LevelBossTest::levelUpdate() {
	dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float playerDT = dt * playerTimeScale;
	timeK += dt;
	updateObjects(objectsList);

	ImGui::SetWindowSize(ImVec2(400, 300));
	ImGui::Begin("Debug Panel");

	tempx2 = tempx;
	tempx = ziz->getTransform().getPosition().y;
	if (tempx2 != tempx) {
		//cout << "Ziz X: " << ziz->getTransform().getPosition().x << endl;
	}
	//cout << "Ziz X: " << ziz->getTransform().getPosition().x << endl;
	/*float distance = abs(ziz->getTransform().getPosition().x - player->getTransform().getPosition().x);
	cout << "Distance: " << distance << endl;*/

	//cout << ziz->getCurrentHealth() << endl;

	if (ziz->getStateMachine()) {
		ziz->getStateMachine()->update(ziz, playerDT);
	}

	if (player->getStateMachine()) {
		player->getStateMachine()->update(player, playerDT);
		//cout << player->getTransform().getPosition().x << endl;
		if (player->getTransform().getPosition().x > 7.5f) {
			player->getTransform().setPosition(glm::vec3(7.5f, player->getTransform().getPosition().y, 0.0f));
		}
		if (player->getTransform().getPosition().x < -7.5f) {
			player->getTransform().setPosition(glm::vec3(-7.5f, player->getTransform().getPosition().y, 0.0f));
		}

	}

	//cout << "player y: " << player->getTransform().getPosition().y << endl;
	
	if (ziz) {
		ziz->phaseChangeTracker();
		ziz->updateShake(dt);
		
	}



	for (DrawableObject* obj : objectsList) {
		
		Gust* gust = dynamic_cast<Gust*>(obj);
		if (gust) {
			gust->update(dt);
		}

		StormRise* stormRise = dynamic_cast<StormRise*>(obj);
		if (stormRise) {
			stormRise->update(dt);
			if (stormRise->getCanAnim()) {
				stormRise->getAnimationComponent()->updateCurrentState(dt);
			}
			
		}

		ChompTentacle* chompTentacle = dynamic_cast<ChompTentacle*>(obj);
		if (chompTentacle) {
			chompTentacle->update(dt);
			chompTentacle->getAnimationComponent()->updateCurrentState(dt);
		}

		Arrow* arrow = dynamic_cast<Arrow*>(obj);
		if (arrow) {
			if (arrow->getFacingDirection()) {
				arrow->getTransform().translate(glm::vec3(arrow->getArrowSpeed() * dt, 0, 0));
			}
			else {
				arrow->getTransform().translate(glm::vec3(-arrow->getArrowSpeed() * dt, 0, 0));
			}

			arrow->selfUpdate(dt);
		}

		SwoopWarning* swoopWarning = dynamic_cast<SwoopWarning*>(obj);
		if (swoopWarning) {
			swoopWarning->update(dt);
		}

		BowUltimateCollider* attackCollider = dynamic_cast<BowUltimateCollider*>(obj);
		if (attackCollider) {
			attackCollider->update(dt);
		}
		

	}



	if (player->getHealth()->getCurrentHP() <= 0) {
		player->setIsDead(true);
		player->setTexture("../Resource/Texture/Dante/dante_Death.png", 1, 1, 0);
		player->getAnimationComponent()->setState("death");
		float xDiff = player->getTransform().getPosition().x - ziz->getTransform().getPosition().x;
		if (xDiff >= 0) {
			//vel+
			player->getPhysicsComponent()->setVelocity(glm::vec2(1.5 * playerTimeScale, 0.8f * playerTimeScale));
		}
		else {
			player->getPhysicsComponent()->setVelocity(glm::vec2(-1.5 * playerTimeScale, 0.8f * playerTimeScale));
		}

		float targetScale = 0.0f;
		float slowdownSpeed = 1.0f; // adjust for faster/slower transition
		float newScale = glm::mix(playerTimeScale, targetScale, slowdownSpeed * dt);
		playerTimeScale = newScale;
	}

	if (ziz->getHealth()->getCurrentHP() <= 0) {
		player->setIsDead(true);
		float targetScale = 0.0f;
		float slowdownSpeed = 1.0f; // adjust for faster/slower transition
		float newScale = glm::mix(playerTimeScale, targetScale, slowdownSpeed * dt);
		playerTimeScale = newScale;
	}


	float healthOriginalWidth = 4.5f;
	float healthBaseX = -5.7f;

	//Health Bar
	float healthPercentage = player->getHealth()->getCurrentHP() / player->getHealth()->getMaxHP();
	healthPercentage = glm::clamp(healthPercentage, 0.0f, 1.0f);

	float healthWidth = healthPercentage * healthOriginalWidth;

	float healthX = healthBaseX - (healthOriginalWidth * 0.5f) + (healthWidth * 0.5f);

	playerHealthBar->getTransform().setScale(glm::vec3(healthWidth, playerHealthBar->getTransform().getScale().y, playerHealthBar->getTransform().getScale().z));
	playerHealthBar->getTransform().setPosition(glm::vec3(healthX, -4.0f, 0.0f));

	//Wither Health Bar
	float totalHealthPercentage = (player->getHealth()->getCurrentHP() + player->getHealth()->getWitherHP()) / player->getHealth()->getMaxHP();
	totalHealthPercentage = glm::clamp(totalHealthPercentage, 0.0f, 1.0f);

	float witherWidth = totalHealthPercentage * healthOriginalWidth;

	float witherX = healthBaseX - (healthOriginalWidth * 0.5f) + (witherWidth * 0.5f);

	witherHealthBar->getTransform().setScale(glm::vec3(witherWidth, witherHealthBar->getTransform().getScale().y, witherHealthBar->getTransform().getScale().z));
	witherHealthBar->getTransform().setPosition(glm::vec3(witherX, -4.0f, 0.0f));

	//Ultimate Bar
	float ultimateOriginalWidth = 2.5f;
	float ultimateBaseX = -6.7f;

	float ultimatePercentage = (player->getUltimateSlot() * 100.0f + player->getUltimateGauge()) / (player->getUltimateSlotMax() * 100.0f);
	ultimatePercentage = glm::clamp(ultimatePercentage, 0.0f, 1.0f);

	float ultimateWidth = ultimatePercentage * ultimateOriginalWidth;

	float ultimateX = ultimateBaseX - (ultimateOriginalWidth * 0.5f) + (ultimateWidth * 0.5f);

	playerUltimateBar->getTransform().setScale(glm::vec3(ultimateWidth, playerUltimateBar->getTransform().getScale().y, playerUltimateBar->getTransform().getScale().z));
	playerUltimateBar->getTransform().setPosition(glm::vec3(ultimateX, -3.65f, 0.0f));

	//Boss Health Bar
	float bossHealthOriginalWidth = 9.0f;
	float bossHealthBaseX = 0.0f;

	float bossHealthPercentage = ziz->getHealth()->getCurrentHP() / ziz->getHealth()->getMaxHP();
	//cout << ziz->getHealth()->getCurrentHP() << " " << ziz->getHealth()->getMaxHP() << endl;
	bossHealthPercentage = glm::clamp(bossHealthPercentage, 0.0f, 1.0f);

	float bossHealthWidth = bossHealthPercentage * bossHealthOriginalWidth;

	float bossHealthX = bossHealthBaseX - (bossHealthOriginalWidth * 0.5f) + (bossHealthWidth * 0.5f);

	bossHealthBar->getTransform().setScale(glm::vec3(bossHealthWidth, bossHealthBar->getTransform().getScale().y, bossHealthBar->getTransform().getScale().z));
	bossHealthBar->getTransform().setPosition(glm::vec3(bossHealthX, 4.0f, 0.0f));

	player->selfUpdate(playerDT);
	player->getSword()->update(playerDT, player);
	player->getBow()->update(playerDT, player);
	player->getShield()->update(playerDT, player);

	player->getAnimationComponent()->updateCurrentState(playerDT);
	ziz->getAnimationComponent()->updateCurrentState(playerDT);
	

	handleObjectCollision(objectsList);

	ImGui::End();
}

void LevelBossTest::levelDraw() {
	GameEngine::getInstance()->render(objectsList);
	//cout << "Draw Level" << endl;
}

void LevelBossTest::levelFree() {
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	//cout << "Free Level" << endl;
}

void LevelBossTest::levelUnload() {
	GameEngine::getInstance()->clearMesh();
	//cout << "Unload Level" << endl;
}

void LevelBossTest::isReceivingNoInputs() {
	cout << "not receieving input" << endl;

	if (player->getIsGrounded()) {
		player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
	}
	player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
}

void LevelBossTest::handleKey(char key) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float speed = 20.0f;
	speed *= dt;

	bool playerIsMoving = false;

	//Jump -> higher priority

	if (player->getIsDead() && key != 'r') return;

	if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
		return;
	}

	switch (key) {
	case 'w':
		//player->getTransform().translate(glm::vec3(0, player->getMovementSpeed() * dt, 0));
		if (player->getIsGrounded()) {
			player->setIsGrounded(false);
			player->getPhysicsComponent()->setVelocity(glm::vec2(player->getPhysicsComponent()->getVelocity().x, 0.0f)); //Set y velocity to 0 before jump to ensure player jump at the same height every time
			player->getPhysicsComponent()->addForce(glm::vec2(0.0f, player->getJumpPower()));
		}
		//player->getAnimationComponent()->setState("up");
		break;
	case 's':
		//player->getTransform().translate(glm::vec3(0, -player->getMovementSpeed() * dt, 0));
		/*player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		playerIsMoving = true;*/
		//player->getAnimationComponent()->setState("down");
		break;
	case 'a':
		if (player->getIsDashing() == true) {
			return;
		}

		player->getPhysicsComponent()->setVelocity(glm::vec2(-player->getMovementSpeed(), player->getPhysicsComponent()->getVelocity().y));
		//player->getTransform().translate(glm::vec3(-player->getMovementSpeed() * dt, 0, 0));
		player->setFacingRight(false);



		playerIsMoving = true;

		if (player->getIsGrounded()) { // only change when walking on ground
			player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		}

		
		//player->getAnimationComponent()->setState("left");
		break;
	case 'd':
		if (player->getIsDashing() == true) {
			return;
		}

		

		player->getPhysicsComponent()->setVelocity(glm::vec2(player->getMovementSpeed(), player->getPhysicsComponent()->getVelocity().y));
		//player->getTransform().translate(glm::vec3(player->getMovementSpeed() * dt, 0, 0));
		player->setFacingRight(true);

		if (player->getIsGrounded()) {
			player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		}

		playerIsMoving = true;
		//player->getAnimationComponent()->setState("right");
		break;
	case 'm':
		//cout << "M pressed" << endl;
		ziz->interruptDeath();
		break;
	case 'q':
		if (player->getWeaponType() == Bow_) {
			//cout << "works" << endl;
			if (player->getUltimateSlot() > 0) {
				if (player->getUltimateSlot() < player->getUltimateSlotMax()) {
					player->increaseUltimateSlot(-1); //decrease ult slot by 1
					//enter small ult
					player->getStateMachine()->changeState(PlayerSmallBowUlt::getInstance(), player);
				}
				else {
					player->increaseUltimateSlot(-player->getUltimateSlotMax()); //decrease ult slot by max
					//enter big ult
					player->getStateMachine()->changeState(PlayerBigBowUlt::getInstance(), player);
				}
			}
		}
		else if (player->getWeaponType() == Sword_) {
			if (player->getUltimateSlot() > 0) {
				if (player->getUltimateSlot() < player->getUltimateSlotMax()) {
					player->increaseUltimateSlot(-1); //decrease ult slot by 1
					//enter small ult
					player->getStateMachine()->changeState(PlayerSmallSwordUlt::getInstance(), player);
				}
				else {
					player->increaseUltimateSlot(-player->getUltimateSlotMax()); //decrease ult slot by max
					//enter big ult
					player->getStateMachine()->changeState(PlayerBigSwordUlt::getInstance(), player);
				}
			}
		}
		else if (player->getWeaponType() == Shield_) {
			if (player->getUltimateSlot() > 0) {
				if (player->getUltimateSlot() < player->getUltimateSlotMax()) {
					player->increaseUltimateSlot(-1); //decrease ult slot by 1
					//enter small ult
					player->getStateMachine()->changeState(PlayerSmallShieldUlt::getInstance(), player);
				}
				else {
					player->increaseUltimateSlot(-player->getUltimateSlotMax()); //decrease ult slot by max
					//enter big ult
					player->getStateMachine()->changeState(PlayerBigShieldUlt::getInstance(), player);
				}
			}
		}
		break;
	case 'r': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART; ; break;
	//case 'e': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_LEVEL1; ; break;
	//case 'f': //player->getBow()->setEnableDebug(); break;
		//player->getHealth()->takeDamage(99);
		//player->increaseUltimateSlot(1);
		break;
	case 'h': 
		player->setWeaponType(Bow_); 
		player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		break;
	case 'j':
		player->setWeaponType(Sword_); 
		player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		break;
	case 'g': 
		player->setWeaponType(Shield_);
		player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		break;
	case 'I': //No Movement Input -> Idle
		
		if (player->getIsGrounded()) {
			player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
			
		}
		if (player->getIsDashing() == false) {
			player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
		}
		
		
		break;
	case 'S': //Spacebar -> Jump
		if (player->getIsDashing() == true) { //Prevent air attack
			return;
		}

		if (player->getIsGrounded()) {
			player->setIsGrounded(false);
			player->getPhysicsComponent()->setVelocity(glm::vec2(player->getPhysicsComponent()->getVelocity().x, 0.0f)); //Set y velocity to 0 before jump to ensure player jump at the same height every time
			player->getPhysicsComponent()->addForce(glm::vec2(0.0f, player->getJumpPower()));
		}
		break;
	case 'P': // dash

		if (player->getTransform().getPosition().x > -7.4f && player->getTransform().getPosition().x < 7.4f) {
			if (player->getCanDash()) {
				player->setMovementSpeed(player->getMovementSpeed() * 5);
				player->setIsDashing(true);
				player->setCanDash(false);
			}
		}
		
		break;
	case 't':
		//ziz->startShake(0.2f, 0.005f);
		player->increaseUltimateGauge(100.0f);
		break;
		
	case 'l':
		//ziz->interruptPhaseChange();
		//cout << "Spawn Tentacle" << endl;
		ziz->createChompTentacle();
		//ziz->resetCam();
		break;
	}


	/*if (!playerIsMoving) {
		player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
	}*/
}

void LevelBossTest::handleControllerButton(SDL_GameControllerButton button) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float speed = 20.0f;
	speed *= dt;

	bool playerIsMoving = false;
	if (player->getIsDead()) return;


	

	switch (button){

	case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
		if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
			return;
		}
		player->getPhysicsComponent()->setVelocity(glm::vec2(-player->getMovementSpeed(), player->getPhysicsComponent()->getVelocity().y));
		//player->getTransform().translate(glm::vec3(-player->getMovementSpeed() * dt, 0, 0));
		player->setFacingRight(false);

		if (player->getIsGrounded()) { // only change when walking on ground
			player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		}

		playerIsMoving = true;
		//player->getAnimationComponent()->setState("left");
		break;

	case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
		if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
			return;
		}
		player->getPhysicsComponent()->setVelocity(glm::vec2(player->getMovementSpeed(), player->getPhysicsComponent()->getVelocity().y));
		//player->getTransform().translate(glm::vec3(player->getMovementSpeed() * dt, 0, 0));
		player->setFacingRight(true);

		if (player->getIsGrounded()) {
			player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
		}

		playerIsMoving = true;
		//player->getAnimationComponent()->setState("right");
		break;
	case SDL_CONTROLLER_BUTTON_X:
		if (player->getIsGrounded() == false || player->getIsDashing() == true) { //Prevent air attack and attack while dashing
			return;
		}

		if (player->getWeaponType() == Bow_) {
			if (player->getBow()->getIsOverheat() == false) {
				if (player->getBow()->getRapidShotReady()) {
					/*DrawableObject* newArrow = bow->arrowShot(10, player, 25);
					objectsList.push_back(newArrow);*/
					player->getStateMachine()->changeState(PlayerLightBowAttack::getInstance(), player);
				}
			}
		}
		else if (player->getWeaponType() == Sword_) {
			if (player->getSword()->getInChainAttack()) {
				//input buffer
				player->getSword()->setInputBuffer(true);
				return;
			}

			switch (player->getSword()->getCurrentChainAttack()) {
			case 0:
				player->getStateMachine()->changeState(PlayerLightSwordAttack1::getInstance(), player);
				break;
				
			}


		}
		else if (player->getWeaponType() == Shield_) {

			if (player->getShield()->getInChainAttack()) {
				player->getShield()->setInputBuffer(true);
				return;
			}

			switch (player->getShield()->getCurrentChainAttack()) {
			case 0:
				player->getStateMachine()->changeState(PlayerLightShieldAttack1::getInstance(), player);
				break;
				
			}
		}


		break;
	case SDL_CONTROLLER_BUTTON_Y:
		if (player->getIsGrounded() == false || player->getIsDashing() == true) { //Prevent air attack and attack while dashing
			return;
		}

		if (player->getWeaponType() == Bow_) {
			player->getStateMachine()->changeState(PlayerHeavyBowAttack::getInstance(), player);
		}
		else if (player->getWeaponType() == Sword_) {
			if (player->getSword()->getInChainAttack()) {
				return;
			}
			player->getStateMachine()->changeState(PlayerHeavySwordAttack::getInstance(), player);
		}
		else if (player->getWeaponType() == Shield_) {
			if (player->getShield()->getInChainAttack()) {
				return;
			}

			player->getStateMachine()->changeState(PlayerShieldGuard::getInstance(), player);
		}
		break;

	case SDL_CONTROLLER_BUTTON_A:
		if (player->getIsDashing() == true) { //Prevent air attack
			return;
		}
		if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
			return;
		}

		if (player->getIsGrounded()) {
			player->setIsGrounded(false);
			player->getPhysicsComponent()->setVelocity(glm::vec2(player->getPhysicsComponent()->getVelocity().x, 0.0f)); //Set y velocity to 0 before jump to ensure player jump at the same height every time
			player->getPhysicsComponent()->addForce(glm::vec2(0.0f, player->getJumpPower()));
		}
		break;
	case SDL_CONTROLLER_BUTTON_B:
		if (player->getTransform().getPosition().x > -7.4f && player->getTransform().getPosition().x < 7.4f) {
			if (player->getCanDash()) {
				player->setMovementSpeed(player->getMovementSpeed() * 4);
				player->setIsDashing(true);
				player->setCanDash(false);
			}
		}
		
		break;
	case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
		if (player->getIsGrounded() == false || player->getIsDashing() == true) { //Prevent air attack and attack while dashing
			return;
		}

		if (player->getWeaponType() == Bow_) {
			//cout << "works" << endl;
			if (player->getUltimateSlot() > 0) {
				if (player->getUltimateSlot() < player->getUltimateSlotMax()) {
					player->increaseUltimateSlot(-1); //decrease ult slot by 1
					//enter small ult
					player->getStateMachine()->changeState(PlayerSmallBowUlt::getInstance(), player);
				}
				else {
					player->increaseUltimateSlot(-player->getUltimateSlotMax()); //decrease ult slot by max
					//enter big ult
					player->getStateMachine()->changeState(PlayerBigBowUlt::getInstance(), player);
				}
			}
		}
		else if (player->getWeaponType() == Sword_) {
			if (player->getUltimateSlot() > 0) {
				if (player->getUltimateSlot() < player->getUltimateSlotMax()) {
					player->increaseUltimateSlot(-1); //decrease ult slot by 1
					//enter small ult
					player->getStateMachine()->changeState(PlayerSmallSwordUlt::getInstance(), player);
				}
				else {
					player->increaseUltimateSlot(-player->getUltimateSlotMax()); //decrease ult slot by max
					//enter big ult
					player->getStateMachine()->changeState(PlayerBigSwordUlt::getInstance(), player);
				}
			}
		}
		else if (player->getWeaponType() == Shield_) {
			if (player->getUltimateSlot() > 0) {
				if (player->getUltimateSlot() < player->getUltimateSlotMax()) {
					player->increaseUltimateSlot(-1); //decrease ult slot by 1
					//enter small ult
					player->getStateMachine()->changeState(PlayerSmallShieldUlt::getInstance(), player);
				}
				else {
					player->increaseUltimateSlot(-player->getUltimateSlotMax()); //decrease ult slot by max
					//enter big ult
					player->getStateMachine()->changeState(PlayerBigShieldUlt::getInstance(), player);
				}
			}
		}

		break;

	default:
		break;
	}
}


void LevelBossTest::handleMouse(int type, int x, int y) {
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;

	GameEngine::getInstance()->getWindowWidth();
	GameEngine::getInstance()->getWindowHeight();

	//cout << "X : " << realX << " Y : " << realY << endl;

	//Check player weapon
	// assume type = bow first

	if (player->getIsDead()) return;

	if (player->getIsGrounded() == false || player->getIsDashing() == true) { //Prevent air attack and attack while dashing
		return;
	}

	if (player->getWeaponType() == Bow_) {
		if (type == 0) {
			if (player->getBow()->getIsOverheat() == false) {
				if (player->getBow()->getRapidShotReady()) {
					/*DrawableObject* newArrow = bow->arrowShot(10, player, 25);
					objectsList.push_back(newArrow);*/
					player->getStateMachine()->changeState(PlayerLightBowAttack::getInstance(), player);
				}
			}
		}
		else if (type == 1) {
			/*DrawableObject* newArrow = bow->arrowShot(100, player, 50);
			objectsList.push_back(newArrow);*/
			player->getStateMachine()->changeState(PlayerHeavyBowAttack::getInstance(), player);
		}
	}
	else if (player->getWeaponType() == Sword_) {
		if (type == 0) {
			//enter first attack of the chain

			if (player->getSword()->getInChainAttack()) {
				//input buffer
				player->getSword()->setInputBuffer(true);
				return;
			}

			switch (player->getSword()->getCurrentChainAttack()) {
			case 0:
				player->getStateMachine()->changeState(PlayerLightSwordAttack1::getInstance(), player);
				break;
				/*case 1:
					player->getStateMachine()->changeState(PlayerLightSwordAttack2::getInstance(), player);
					break;
				case 2:
					player->getStateMachine()->changeState(PlayerLightSwordAttack3::getInstance(), player);
					break;*/
			}


		}
		else if (type == 1) {
			if (player->getSword()->getInChainAttack()) {
				return;
			}

			player->getStateMachine()->changeState(PlayerHeavySwordAttack::getInstance(), player);
		}

	}
	else if (player->getWeaponType() == Shield_) {
		if (type == 0) {
			//enter first attack of the chain

			if (player->getShield()->getInChainAttack()) {
				//input buffer
				player->getShield()->setInputBuffer(true);
				return;
			}

			switch (player->getShield()->getCurrentChainAttack()) {
			case 0:
				player->getStateMachine()->changeState(PlayerLightShieldAttack1::getInstance(), player);
				break;
				/*case 1:
					player->getStateMachine()->changeState(PlayerLightSwordAttack2::getInstance(), player);
					break;
				case 2:
					player->getStateMachine()->changeState(PlayerLightSwordAttack3::getInstance(), player);
					break;*/
			}


		}
		else if (type == 1) {
			if (player->getShield()->getInChainAttack()) {
				return;
			}

			player->getStateMachine()->changeState(PlayerShieldGuard::getInstance(), player);
		}
		else if (type == 3) {

			if (player->getShield()->getIsBlocking()) {
				player->getStateMachine()->changeState(PlayerOffShield::getInstance(), player);
			}
		}
	}
}

void LevelBossTest::handleAnalogStick(int type, char key) {
	float dt_ = GameEngine::getInstance()->getTime()->getDeltaTime();
	float speed = 20.0f;
	speed *= dt_;
	bool playerIsMoving = false;

	if (player->getIsDead()) return;


	if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
		return;
	}
	

	if (type == 0) {//x axis
		switch (key) {
		case 'l':
			//cout << "Tilt Left" << endl;
			player->getPhysicsComponent()->setVelocity(glm::vec2(-player->getMovementSpeed(), player->getPhysicsComponent()->getVelocity().y));
			//player->getTransform().translate(glm::vec3(-player->getMovementSpeed() * dt, 0, 0));
			player->setFacingRight(false);

			if (player->getIsGrounded()) { // only change when walking on ground
				player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
			}

			playerIsMoving = true;
			//player->getAnimationComponent()->setState("left");

			break;
		case  'r':
			//cout << "Tilt Right" << endl;
			player->getPhysicsComponent()->setVelocity(glm::vec2(player->getMovementSpeed(), player->getPhysicsComponent()->getVelocity().y));
			//player->getTransform().translate(glm::vec3(player->getMovementSpeed() * dt, 0, 0));
			player->setFacingRight(true);

			if (player->getIsGrounded()) {
				player->getStateMachine()->changeState(PlayerWalkState::getInstance(), player);
			}

			playerIsMoving = true;
			//player->getAnimationComponent()->setState("right");

			break;

		}
	}
}

void LevelBossTest::addObject(DrawableObject* obj) {
	objectsList.push_back(obj);
}

void LevelBossTest::addPlayerToDebug(Player* player) {

}