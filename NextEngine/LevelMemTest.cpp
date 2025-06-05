#include "LevelMemTest.h"
#include "CollisionHandler.h"
#include "Bow.h"
#include "ZizGroundSlamState.h"
#include "GameEngine.h" // Include GameEngine header
#include "GLRenderer.h" // Include GLRenderer header
#include <iostream>
#include <random>
#include <fstream>
using namespace std;




void LevelMemTest::levelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->loadData();
	GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

	SquareBorderMesh* border = new SquareBorderMesh();
	border->loadData();
	GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);
}

void LevelMemTest::levelInit() {
	currentControlType = ControlType::keyboard;

	TexturedObject* background = new TexturedObject("background");
	background->setTexture("../Resource/Texture/Lust_Alpha.png");
	background->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	objectsList.push_back(background);


	Player* player_ = GameEngine::getInstance()->loadPlayerData("../Resource/Saves/PlayerData/playerData.txt");
	objectsList.push_back(player_);
	player = player_;
	player->setLevel(this);
	player->getTransform().setPosition(glm::vec3(-5.0, -0.8f, 0.0f));
	objectsList.push_back(player->getGroundChecker());

	player->setWeaponType(Bow_);
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


	//Ziz* ziz_ = new Ziz();
	//objectsList.push_back(ziz_);
	//ziz = ziz_;
	//ziz->setLevel(this);
	//ziz->setPlayer(player);
	//ziz->setIdleState();


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

	//Overheat
	TexturedObject* overheatBarBackground = new TexturedObject("Overheat Background");
	overheatBarBackground->setTexture("../Resource/Texture/UI/Bow/Overheat_Empty_BG.png");
	overheatBarBackground->getTransform().setScale(glm::vec3(1.37f * 2.75f, 0.02f * 4.5f, 1.0f));
	overheatBarBackground->getTransform().setPosition(glm::vec3(-4.1f, -3.55f, 0.0f));
	objectsList.push_back(overheatBarBackground);
	playerOverheatBarBackground = overheatBarBackground;

	SimpleObject* overheatBar = new SimpleObject("Overheat Bar");
	overheatBar->setColor(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f);
	overheatBar->getTransform().setScale(glm::vec3(3.665f, 0.08f, 0.0f));
	overheatBar->getTransform().setPosition(glm::vec3(-4.1f, -3.55f, 0.0f));
	objectsList.push_back(overheatBar);
	playerOverheatBar = overheatBar;

	TexturedObject* overheatBarFrame = new TexturedObject("Overheat Frame");
	overheatBarFrame->setTexture("../Resource/Texture/UI/Bow/Overheat_Frame.png");
	overheatBarFrame->getTransform().setScale(glm::vec3(1.37f * 2.75f, 0.02f * 4.5f, 1.0f));
	overheatBarFrame->getTransform().setPosition(glm::vec3(-4.1f, -3.55f, 0.0f));
	objectsList.push_back(overheatBarFrame);
	playerOverheatBarFrame = overheatBarFrame;

	//Health & Ult UI
	//cout << "Init Level" << endl;
	TexturedObject* healthBarBackground = new TexturedObject("Health Background");
	healthBarBackground->setTexture("../Resource/Texture/UI/Healthbar_BG.png");
	healthBarBackground->getTransform().setScale(glm::vec3(2.42f * 2.5f, 0.5f * 2.5f, 1.0f));
	healthBarBackground->getTransform().setPosition(glm::vec3(-5.0f, -4.0f, 0.0f));
	objectsList.push_back(healthBarBackground);

	SimpleObject* witherHealthBar_ = new SimpleObject("Wither Health Bar");
	witherHealthBar_->setColor(106.0f / 255.0f, 109.0f / 255.0f, 115.0f / 255.0f);
	witherHealthBar_->getTransform().setScale(glm::vec3(5.375f, 0.23f, 0.0f));
	witherHealthBar_->getTransform().setPosition(glm::vec3(-5.05f, -3.95f, 0.0f));
	objectsList.push_back(witherHealthBar_);
	witherHealthBar = witherHealthBar_;

	SimpleObject* healthBar = new SimpleObject("Health Bar");
	healthBar->setColor(1.0f, 0.0f, 0.0f);
	healthBar->getTransform().setScale(glm::vec3(5.375f, 0.23f, 0.0f));
	healthBar->getTransform().setPosition(glm::vec3(-5.05f, -3.95f, 0.0f));
	objectsList.push_back(healthBar);
	playerHealthBar = healthBar;

	SimpleObject* ultimateBar = new SimpleObject("Ultimate Bar");
	ultimateBar->setColor(235.0f / 255.0f, 168.0f / 255.0f, 52.0f / 255.0f);
	ultimateBar->getTransform().setScale(glm::vec3(3.18f, 0.25f, 0.0f));
	ultimateBar->getTransform().setPosition(glm::vec3(-6.165f, -4.225f, 0.0f));
	objectsList.push_back(ultimateBar);
	playerUltimateBar = ultimateBar;

	TexturedObject* healthBarFrame = new TexturedObject("Health Frame");
	healthBarFrame->setTexture("../Resource/Texture/UI/Healthbar_Frame.png");
	healthBarFrame->getTransform().setScale(glm::vec3(2.42f * 2.5f, 0.5f * 2.5f, 1.0f));
	healthBarFrame->getTransform().setPosition(glm::vec3(-5.0f, -4.0f, 0.0f));
	objectsList.push_back(healthBarFrame);

	SimpleObject* bossHealthBar_ = new SimpleObject("Boss Health Bar");
	bossHealthBar_->setColor(0.0f, 1.0f, 0.0f);
	bossHealthBar_->getTransform().setScale(glm::vec3(9.0f, 0.25f, 0.0f));
	bossHealthBar_->getTransform().setPosition(glm::vec3(0.0f, 4.0f, 0.0f));
	objectsList.push_back(bossHealthBar_);
	bossHealthBar = bossHealthBar_;

	createSkillsIcon();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Black Fading Transition
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* blackFade_ = new TexturedObject("Black Fade");
	blackFade_->setTexture("../Resource/Texture/blackFade.png");
	blackFade_->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	objectsList.push_back(blackFade_);
	blackFade = blackFade_;
	blackFade->setAlpha(1.0f);
	firstStart = true;

	createPauseUI();

	GameEngine::getInstance()->freezeGameForSecond(0.6f);
	inputManager = GameEngine::getInstance()->getInputHandler();
}

void LevelMemTest::levelUpdate() {
	dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float playerDT = dt * playerTimeScale;
	timeK += dt;

	UIUpdate();

	if (isPausing(dt)) {
		return;
	}

	updateObjects(objectsList);
	updateSkillsIcon();

	//std::cout << "Current cache size: " << GameEngine::getInstance()->getRenderer()->getTextureCache().size() << std::endl;
	/*if (currentControlType == ControlType::controller) {
		cout << "Current Control Scheme: Controller" << endl;
	}
	if (currentControlType == ControlType::keyboard) {
		cout << "Current Control Scheme: Keyboard" << endl;
	}*/


	/*if (inputManager) {
		if (inputManager->getLastInput() == InputDevice::KEYBOARD) {
			cout << "inputmanager last Keyboard" << endl;
		}
		else {
			cout << "inputmanager last controller" << endl;
		}
	}*/


	if (firstStart) {
		if (blackFade) {
			blackFadeTransitionTime += dt;
			float t = blackFadeTransitionTime / blackFadeTransitionDuration;
			bool finishBlackFade = false;
			if (t >= 1.0f) {
				t = 1.0f;
				finishBlackFade = true;
			}

			blackFade->setAlpha(1.0f - t);

			if (finishBlackFade) {
				firstStart = false;
				blackFade->setAlpha(0.0f);
			}
		}
	}

	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	for (UIButton* button : buttonsList) {
		button->isHovered(mouseX, mouseY);
	}

	stateMachineUpdate(playerDT);

	//if (ziz) {
	//	ziz->phaseChangeTracker();
	//	ziz->updateShake(dt);
	//	ziz->update(dt);

	//}

	if (player) {
		player->updateShake(dt);
		//cout << player->getHealth()->getCurrentHP() << endl;
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

		QTEButtonUI* qteButtonUI = dynamic_cast<QTEButtonUI*>(obj);
		if (qteButtonUI) {
			qteButtonUI->update(dt);
		}

		UltZizOnBG* ultZizOnBG = dynamic_cast<UltZizOnBG*>(obj);
		if (ultZizOnBG) {
			ultZizOnBG->update(dt);
		}

		Lightning* lightning = dynamic_cast<Lightning*>(obj);
		if (lightning) {
			//cout << "lightning found" << endl;
			lightning->update(dt);
			lightning->getAnimationComponent()->updateCurrentState(dt);
		}

		Impale* impale = dynamic_cast<Impale*>(obj);
		if (impale) {
			impale->update(dt);
			impale->getAnimationComponent()->updateCurrentState(dt);
		}

		BowUltimateCollider* bowUltCol = dynamic_cast<BowUltimateCollider*>(obj);
		if (bowUltCol) {
			bowUltCol->update(dt);
		}

		PlayerAttackCollider* playerAttackCol = dynamic_cast<PlayerAttackCollider*>(obj);
		if (playerAttackCol) {
			if (playerAttackCol->isAnimated()) {
				playerAttackCol->getAnimationComponent()->updateCurrentState(dt);
			}
		}

		UIText* text = dynamic_cast<UIText*>(obj);
		if (text) {
			text->update(dt);
		}

		UIButton* button = dynamic_cast<UIButton*>(obj);
		if (button) {
			button->update(dt);
		}
	}



	if (player->getHealth()->getCurrentHP() <= 0) {
		player->setIsDead(true);
		player->setTexture("../Resource/Texture/Dante/dante_Death.png", 1, 1, 0);
		player->getAnimationComponent()->setState("death");
		float xDiff = player->getTransform().getPosition().x;
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

	//if (ziz->getHealth()->getCurrentHP() <= 0) {
	//	player->setIsDead(true);
	//	float targetScale = 0.0f;
	//	float slowdownSpeed = 1.0f; // adjust for faster/slower transition
	//	float newScale = glm::mix(playerTimeScale, targetScale, slowdownSpeed * dt);
	//	playerTimeScale = newScale;
	//}

	updateUIBar();

	player->selfUpdate(playerDT);
	player->getSword()->update(playerDT, player);
	player->getBow()->update(playerDT, player);
	player->getShield()->update(playerDT, player);

	player->getAnimationComponent()->updateCurrentState(playerDT);
	//ziz->getAnimationComponent()->updateCurrentState(playerDT);


	handleObjectCollision(objectsList);

	ImGui::End();
}

void LevelMemTest::levelDraw() {
	GameEngine::getInstance()->render(objectsList);
	//cout << "Draw Level" << endl;
}

void LevelMemTest::levelFree() {
	//savePlayerData(player, "../Resource/Saves/PlayerData/playerData.txt");

	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	buttonsFree();
}

void LevelMemTest::levelUnload() {
	GameEngine::getInstance()->clearMesh();
	//cout << "Unload Level" << endl;
}

void LevelMemTest::isReceivingNoInputs() {
	cout << "not receieving input" << endl;

	if (player->getIsGrounded()) {
		player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
	}
	player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
}

void LevelMemTest::switchControlType(ControlType ct) {
	switch (ct) {
	case ControlType::keyboard:
		if (currentControlType != ControlType::keyboard) {
			currentControlType = ControlType::keyboard;
		}
		break;
	case ControlType::controller:
		if (currentControlType != ControlType::controller) {
			currentControlType = ControlType::controller;
		}
		break;
	default:
		break;
	}

}

void LevelMemTest::handleKey(char key) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float speed = 20.0f;
	speed *= dt;

	bool playerIsMoving = false;

	if (currentMenuState != MenuState::MAIN) {
		if (key == 't') {
			changeMenuState(MenuState::MAIN);
		}
		else if (key == 'l') {
			changeMenuState(MenuState::PAUSE);
		}
		keyboardUIHandling(key);
		return;
	}



	/*if (ziz->getQTEMode() == true) {
		if (key != 'I') {
			if ((key == 'w') || (key == 'a') || (key == 's') || (key == 'd')) {
				switch (key) {
				case 'w':
					ziz->handleQTEInput(0);
					break;
				case 'a':
					ziz->handleQTEInput(1);
					break;
				case 's':
					ziz->handleQTEInput(2);
					break;
				case 'd':
					ziz->handleQTEInput(3);
					break;
				default:
					break;
				}
				return;
			}
		}
	}*/

	//Jump -> higher priority

	if (player->getIsDead() && key != 'r') return;

	if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
		return;
	}




	switch (key) {
	case 'w':
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;

		switchControlType(keyboard);
		if (player->getIsGrounded()) {
			player->setIsGrounded(false);
			player->getPhysicsComponent()->setVelocity(glm::vec2(player->getPhysicsComponent()->getVelocity().x, 0.0f)); //Set y velocity to 0 before jump to ensure player jump at the same height every time
			player->getPhysicsComponent()->addForce(glm::vec2(0.0f, player->getJumpPower()));
		}

		break;
	case 's':
		switchControlType(keyboard);
		break;
	case 'a':
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;
		switchControlType(keyboard);

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
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;
		switchControlType(keyboard);



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
		//ziz->interruptDeath();
		break;
	case 'q':
		if (player->getIsGrounded() == false) return;
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;
		switchControlType(keyboard);
		playerUltimateInput();
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

		if (player->getIsDashing() == false) {
			player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
		}

		if (player->getIsGrounded()) {
			player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
		}



		break;
	case 'S': //Spacebar -> Jump
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;
		switchControlType(keyboard);
		if (player->getIsGrounded()) {
			player->setIsGrounded(false);
			player->getPhysicsComponent()->setVelocity(glm::vec2(player->getPhysicsComponent()->getVelocity().x, 0.0f)); //Set y velocity to 0 before jump to ensure player jump at the same height every time
			player->getPhysicsComponent()->addForce(glm::vec2(0.0f, player->getJumpPower()));
		}
		break;
	case 'P': // dash
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;
		switchControlType(keyboard);
		if (player->getTransform().getPosition().x > -7.4f && player->getTransform().getPosition().x < 7.4f) {
			if (player->getCanDash()) {
				player->setMovementSpeed(player->getMovementSpeed() * 5);
				player->setIsDashing(true);
				player->setCanDash(false);
			}
		}

		break;
	case 't':
		//player->startShake(0.1f, 0.0025f);
		//ziz->startShake(0.2f, 0.005f);
		player->increaseUltimateGauge(100.0f);
		//ziz->interruptPhaseChange();
		//currentMenuState = MenuState::MAIN;
		/*qbui = new QTEButtonUI(0);
		objectsList.push_back(qbui);*/
		//ziz->interruptIntoPhase();

		break;

	case 'l':

		changeMenuState(MenuState::PAUSE);
		/*UltZizOnBG* ultZizOnBG_ = ziz->createBGZiz();
		addObject(ultZizOnBG_);
		ziz->startShake(0.08f * (12*3.75), 0.0025f);*/

		/*DrawableObject* lightning_ = ziz->createLightning();
		addObject(lightning_);*/

		/*DrawableObject* newStormRise = ziz->createStormRise();
		addObject(newStormRise);*/

		/*DrawableObject* newGust = ziz->createGust();
		addObject(newGust);*/
		//qbui->expire();

		//ziz->interruptIntoPhase();
		//ziz->interruptPhaseChange();

		//ziz->startShake(0.2f, 0.005f);

		//ziz->createChompTentacle();
		//ziz->resetCam();
		break;
	}


	/*if (!playerIsMoving) {
		player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
	}*/
}

void LevelMemTest::handleControllerButton(SDL_GameControllerButton button) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float speed = 20.0f;
	speed *= dt;

	if (currentMenuState != MenuState::MAIN) {
		return;
	}


	bool playerIsMoving = false;
	if (player->getIsDead()) return;


	/*if (ziz->getQTEMode() == true) {
		if ((button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) || (button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) || (button == SDL_CONTROLLER_BUTTON_DPAD_UP) || (button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
			switch (button) {
			case SDL_CONTROLLER_BUTTON_DPAD_UP:
				ziz->handleQTEInput(0);
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
				ziz->handleQTEInput(1);
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
				ziz->handleQTEInput(2);
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
				ziz->handleQTEInput(3);
				break;
			default:
				break;
			}
			return;
		}
	}*/



	switch (button) {

	case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
		if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
			return;
		}
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;
		switchControlType(controller);

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
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;
		switchControlType(controller);

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
		if (player->getIsGrounded() == false) return;
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;
		switchControlType(controller);

		if (player->getWeaponType() == Bow_) {
			if (player->getBow()->getIsShooting() == true) return;
			if (player->getBow()->getIsOverheat() == false) {
				if (player->getBow()->getRapidShotReady()) {
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
		if (player->getIsGrounded() == false) return;
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;


		if (player->getWeaponType() == Bow_) {
			if (player->getBow()->getIsShooting() == true) return;
			if (player->getBow()->getIsOverheat() == false) {
				player->getStateMachine()->changeState(PlayerHeavyBowAttack::getInstance(), player);
			}
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
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;
		if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
			return;
		}

		switchControlType(controller);
		if (player->getIsGrounded()) {
			player->setIsGrounded(false);
			player->getPhysicsComponent()->setVelocity(glm::vec2(player->getPhysicsComponent()->getVelocity().x, 0.0f)); //Set y velocity to 0 before jump to ensure player jump at the same height every time
			player->getPhysicsComponent()->addForce(glm::vec2(0.0f, player->getJumpPower()));
		}
		break;
	case SDL_CONTROLLER_BUTTON_B:
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;
		if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
			return;
		}
		switchControlType(controller);

		if (player->getTransform().getPosition().x > -7.4f && player->getTransform().getPosition().x < 7.4f) {
			if (player->getCanDash()) {
				player->setMovementSpeed(player->getMovementSpeed() * 4);
				player->setIsDashing(true);
				player->setCanDash(false);
			}
		}

		break;
	case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
		if (player->getIsGrounded() == false) return;
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;
		if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
			return;
		}
		switchControlType(controller);
		//ziz->interruptIntoPhase();
		playerUltimateInput();

		break;

	default:
		break;
	}
}


void LevelMemTest::handleMouse(int type, int x, int y) {
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;

	GameEngine::getInstance()->getWindowWidth();
	GameEngine::getInstance()->getWindowHeight();

	if (currentMenuState != MenuState::MAIN) {
		mouseUIHandling(type, x, y);
		return;
	}

	//cout << "X : " << realX << " Y : " << realY << endl;

	for (UIButton* button : buttonsList) {
		if (button->getMouseOver()) {
			if (type == 0) {
				GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART;
			}
		}
	}

	//Check player weapon
	// assume type = bow first

	if (player->getIsDead()) return;
	if (player->getIsGrounded() == false) return;
	if (player->getIsDashing() == true) return;
	if (player->getIsStunned() == true) return;


	if (player->getWeaponType() == Bow_) {
		if (player->getBow()->getIsShooting() == true) return;

		if (type == 0) {
			switchControlType(keyboard);
			if (player->getBow()->getIsOverheat() == false) {
				if (player->getBow()->getRapidShotReady()) {
					player->getStateMachine()->changeState(PlayerLightBowAttack::getInstance(), player);
				}
			}
		}
		else if (type == 1) {
			switchControlType(keyboard);
			if (player->getBow()->getIsOverheat() == false) {
				player->getStateMachine()->changeState(PlayerHeavyBowAttack::getInstance(), player);
			}
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
			switchControlType(keyboard);
			switch (player->getSword()->getCurrentChainAttack()) {
			case 0:
				player->getStateMachine()->changeState(PlayerLightSwordAttack1::getInstance(), player);
				break;
			}


		}
		else if (type == 1) {
			if (player->getSword()->getInChainAttack()) {
				return;
			}
			switchControlType(keyboard);
			player->getStateMachine()->changeState(PlayerHeavySwordAttack::getInstance(), player);
		}

	}
	else if (player->getWeaponType() == Shield_) {
		if (type == 0) {
			//enter first attack of the chain
			if (player->getShield()->getIsBlocking()) {
				return;
			}

			if (player->getShield()->getInChainAttack()) {
				//input buffer
				player->getShield()->setInputBuffer(true);
				return;
			}


			switchControlType(keyboard);
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
			switchControlType(keyboard);
			player->getStateMachine()->changeState(PlayerShieldGuard::getInstance(), player);
		}
		else if (type == 3) {
			switchControlType(keyboard);
			if (player->getShield()->getIsBlocking()) {
				player->getStateMachine()->changeState(PlayerOffShield::getInstance(), player);
			}
		}
	}
}

void LevelMemTest::handleAnalogStick(int type, char key) {
	float dt_ = GameEngine::getInstance()->getTime()->getDeltaTime();
	float speed = 20.0f;
	speed *= dt_;
	bool playerIsMoving = false;

	if (currentMenuState != MenuState::MAIN) {
		return;
	}

	if (player->getIsDead()) return;


	if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
		return;
	}

	if (type == 0) {//x axis
		switchControlType(controller);
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

void LevelMemTest::addObject(DrawableObject* obj) {
	objectsList.push_back(obj);
}

void LevelMemTest::addPlayerToDebug(Player* player) {

}

void LevelMemTest::createSkillsIcon() {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Bow Skills Icon
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* bowSmallUltIconOff_ = new TexturedObject("Bow Small Ultimate Icon Off");
	bowSmallUltIconOff_->setTexture("../Resource/Texture/UI/Skills/Bow_Min_Off.png");
	bowSmallUltIconOff_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	bowSmallUltIconOff_->getTransform().setPosition(glm::vec3(-7.4f, -3.375f, 1.0f));
	objectsList.push_back(bowSmallUltIconOff_);
	bowSmallUltIconOff = bowSmallUltIconOff_;

	TexturedObject* bowSmallUltIconOn_ = new TexturedObject("Bow Small Ultimate Icon On");
	bowSmallUltIconOn_->setTexture("../Resource/Texture/UI/Skills/Bow_Min_On.png");
	bowSmallUltIconOn_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	bowSmallUltIconOn_->getTransform().setPosition(glm::vec3(-7.4f, -3.375f, 1.0f));
	objectsList.push_back(bowSmallUltIconOn_);
	bowSmallUltIconOn = bowSmallUltIconOn_;

	TexturedObject* bowBigUltIconOff_ = new TexturedObject("Bow Big Ultimate Icon Off");
	bowBigUltIconOff_->setTexture("../Resource/Texture/UI/Skills/Bow_Max_Off.png");
	bowBigUltIconOff_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	bowBigUltIconOff_->getTransform().setPosition(glm::vec3(-6.55f, -3.375f, 1.0f));
	objectsList.push_back(bowBigUltIconOff_);
	bowBigUltIconOff = bowBigUltIconOff_;

	TexturedObject* bowBigUltIconOn_ = new TexturedObject("Bow Big Ultimate Icon On");
	bowBigUltIconOn_->setTexture("../Resource/Texture/UI/Skills/Bow_Max_On.png");
	bowBigUltIconOn_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	bowBigUltIconOn_->getTransform().setPosition(glm::vec3(-6.55f, -3.375f, 1.0f));
	objectsList.push_back(bowBigUltIconOn_);
	bowBigUltIconOn = bowBigUltIconOn_;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Sword Skills Icon
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* swordSmallUltIconOff_ = new TexturedObject("Sword Small Ultimate Icon Off");
	swordSmallUltIconOff_->setTexture("../Resource/Texture/UI/Skills/Sword_Min_Off.png");
	swordSmallUltIconOff_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	swordSmallUltIconOff_->getTransform().setPosition(glm::vec3(-7.4f, -3.375f, 1.0f));
	objectsList.push_back(swordSmallUltIconOff_);
	swordSmallUltIconOff = swordSmallUltIconOff_;

	TexturedObject* swordSmallUltIconOn_ = new TexturedObject("Sword Small Ultimate Icon On");
	swordSmallUltIconOn_->setTexture("../Resource/Texture/UI/Skills/Sword_Min_On.png");
	swordSmallUltIconOn_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	swordSmallUltIconOn_->getTransform().setPosition(glm::vec3(-7.4f, -3.375f, 1.0f));
	objectsList.push_back(swordSmallUltIconOn_);
	swordSmallUltIconOn = swordSmallUltIconOn_;

	TexturedObject* swordBigUltIconOff_ = new TexturedObject("Sword Big Ultimate Icon Off");
	swordBigUltIconOff_->setTexture("../Resource/Texture/UI/Skills/Sword_Max_Off.png");
	swordBigUltIconOff_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	swordBigUltIconOff_->getTransform().setPosition(glm::vec3(-6.55f, -3.375f, 1.0f));
	objectsList.push_back(swordBigUltIconOff_);
	swordBigUltIconOff = swordBigUltIconOff_;

	TexturedObject* swordBigUltIconOn_ = new TexturedObject("Sword Big Ultimate Icon On");
	swordBigUltIconOn_->setTexture("../Resource/Texture/UI/Skills/Sword_Max_On.png");
	swordBigUltIconOn_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	swordBigUltIconOn_->getTransform().setPosition(glm::vec3(-6.55f, -3.375f, 1.0f));
	objectsList.push_back(swordBigUltIconOn_);
	swordBigUltIconOn = swordBigUltIconOn_;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Shield Skills Icon
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* shieldSmallUltIconOff_ = new TexturedObject("Shield Small Ultimate Icon Off");
	shieldSmallUltIconOff_->setTexture("../Resource/Texture/UI/Skills/Shield_Min_Off.png");
	shieldSmallUltIconOff_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	shieldSmallUltIconOff_->getTransform().setPosition(glm::vec3(-7.4f, -3.375f, 1.0f));
	objectsList.push_back(shieldSmallUltIconOff_);
	shieldSmallUltIconOff = shieldSmallUltIconOff_;

	TexturedObject* shieldSmallUltIconOn_ = new TexturedObject("Shield Small Ultimate Icon On");
	shieldSmallUltIconOn_->setTexture("../Resource/Texture/UI/Skills/Shield_Min_On.png");
	shieldSmallUltIconOn_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	shieldSmallUltIconOn_->getTransform().setPosition(glm::vec3(-7.4f, -3.375f, 1.0f));
	objectsList.push_back(shieldSmallUltIconOn_);
	shieldSmallUltIconOn = shieldSmallUltIconOn_;

	TexturedObject* shieldBigUltIconOff_ = new TexturedObject("Shield Big Ultimate Icon Off");
	shieldBigUltIconOff_->setTexture("../Resource/Texture/UI/Skills/Shield_Max_Off.png");
	shieldBigUltIconOff_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	shieldBigUltIconOff_->getTransform().setPosition(glm::vec3(-6.55f, -3.375f, 1.0f));
	objectsList.push_back(shieldBigUltIconOff_);
	shieldBigUltIconOff = shieldBigUltIconOff_;

	TexturedObject* shieldBigUltIconOn_ = new TexturedObject("Shield Big Ultimate Icon On");
	shieldBigUltIconOn_->setTexture("../Resource/Texture/UI/Skills/Shield_Max_On.png");
	shieldBigUltIconOn_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	shieldBigUltIconOn_->getTransform().setPosition(glm::vec3(-6.55f, -3.375f, 1.0f));
	objectsList.push_back(shieldBigUltIconOn_);
	shieldBigUltIconOn = shieldBigUltIconOn_;
}

void LevelMemTest::updateSkillsIcon() {

	TexturedObject* smallUltOff = nullptr;
	TexturedObject* smallUltOn = nullptr;
	TexturedObject* bigUltOff = nullptr;
	TexturedObject* bigUltOn = nullptr;
	bool smallUltReady = false;
	bool bigUltReady = false;

	swordSmallUltIconOff->setDraw(false);
	swordSmallUltIconOn->setDraw(false);
	swordBigUltIconOff->setDraw(false);
	swordBigUltIconOn->setDraw(false);

	bowSmallUltIconOff->setDraw(false);
	bowSmallUltIconOn->setDraw(false);
	bowBigUltIconOff->setDraw(false);
	bowBigUltIconOn->setDraw(false);
	playerOverheatBarBackground->setDraw(false);
	playerOverheatBar->setDraw(false);
	playerOverheatBarFrame->setDraw(false);

	shieldSmallUltIconOff->setDraw(false);
	shieldSmallUltIconOn->setDraw(false);
	shieldBigUltIconOff->setDraw(false);
	shieldBigUltIconOn->setDraw(false);


	if (player) {
		WeaponType playerWeapon = player->getWeaponType();
		if (playerWeapon) {
			switch (playerWeapon) {
			case None_:
				return;
				break;
			case Sword_:
				smallUltOff = swordSmallUltIconOff;
				smallUltOn = swordSmallUltIconOn;
				bigUltOff = swordBigUltIconOff;
				bigUltOn = swordBigUltIconOn;
				smallUltReady = player->getSword()->getSmallUltReady();
				bigUltReady = player->getSword()->getBigUltReady();
				break;
			case Bow_:
				smallUltOff = bowSmallUltIconOff;
				smallUltOn = bowSmallUltIconOn;
				bigUltOff = bowBigUltIconOff;
				bigUltOn = bowBigUltIconOn;
				smallUltReady = player->getBow()->getSmallUltReady();
				bigUltReady = player->getBow()->getBigUltReady();
				playerOverheatBarBackground->setDraw(true);
				playerOverheatBar->setDraw(true);
				playerOverheatBarFrame->setDraw(true);
				break;
			case Shield_:
				smallUltOff = shieldSmallUltIconOff;
				smallUltOn = shieldSmallUltIconOn;
				bigUltOff = shieldBigUltIconOff;
				bigUltOn = shieldBigUltIconOn;
				smallUltReady = player->getShield()->getSmallUltReady();
				bigUltReady = player->getShield()->getBigUltReady();
				break;
			}


			if (player->getUltimateSlot() >= 1) {
				if (smallUltReady) {
					smallUltOff->setDraw(false);
					smallUltOn->setDraw(true);
				}
				else {
					smallUltOff->setDraw(true);
					smallUltOn->setDraw(false);
				}
			}
			else if (player->getUltimateSlot() == 0) {
				smallUltOff->setDraw(true);
				smallUltOn->setDraw(false);
			}

			if (player->getUltimateSlot() == player->getUltimateSlotMax()) {
				if (bigUltReady) {
					bigUltOff->setDraw(false);
					bigUltOn->setDraw(true);
				}
				else {
					bigUltOff->setDraw(true);
					bigUltOn->setDraw(false);
				}
			}
			else {
				bigUltOff->setDraw(true);
				bigUltOn->setDraw(false);
			}
		}
	}
}

void LevelMemTest::playerUltimateInput() {
	if (player->getIsGrounded() == false || player->getIsDashing() == true) { //Prevent air attack and attack while dashing
		return;
	}

	if (player->getWeaponType() == Bow_) {
		//cout << "works" << endl;


		if (player->getUltimateSlot() > 0) {
			if (player->getUltimateSlot() < player->getUltimateSlotMax()) {
				if (player->getBow()->getSmallUltReady()) {
					player->increaseUltimateSlot(-1); //decrease ult slot by 1
					//enter small ult
					player->getStateMachine()->changeState(PlayerSmallBowUlt::getInstance(), player);
				}
			}
			else {
				if (player->getBow()->getBigUltReady()) {
					player->increaseUltimateSlot(-player->getUltimateSlotMax()); //decrease ult slot by max
					//enter big ult
					player->getStateMachine()->changeState(PlayerBigBowUlt::getInstance(), player);
				}
			}
		}
	}
	else if (player->getWeaponType() == Sword_) {
		if (player->getUltimateSlot() > 0) {
			if (player->getUltimateSlot() < player->getUltimateSlotMax()) {
				if (player->getSword()->getSmallUltReady()) {
					player->increaseUltimateSlot(-1); //decrease ult slot by 1
					//enter small ult
					player->getStateMachine()->changeState(PlayerSmallSwordUlt::getInstance(), player);
				}
			}
			else {
				if (player->getSword()->getBigUltReady()) {
					player->increaseUltimateSlot(-player->getUltimateSlotMax()); //decrease ult slot by max
					//enter big ult
					player->getStateMachine()->changeState(PlayerBigSwordUlt::getInstance(), player);
				}
			}
		}
	}
	else if (player->getWeaponType() == Shield_) {
		if (player->getUltimateSlot() > 0) {
			if (player->getUltimateSlot() < player->getUltimateSlotMax()) {
				if (player->getShield()->getSmallUltReady()) {
					player->increaseUltimateSlot(-1); //decrease ult slot by 1
					//enter small ult
					player->getStateMachine()->changeState(PlayerSmallShieldUlt::getInstance(), player);
				}
			}
			else {
				if (player->getShield()->getBigUltReady()) {
					player->increaseUltimateSlot(-player->getUltimateSlotMax()); //decrease ult slot by max
					//enter big ult
					player->getStateMachine()->changeState(PlayerBigShieldUlt::getInstance(), player);
				}
			}
		}
	}
}

void LevelMemTest::updateUIBar() {
	static float healthOriginalWidth = playerHealthBar->getTransform().getScale().x;
	static float healthBaseX = playerHealthBar->getTransform().getPosition().x;

	//Health Bar
	float healthPercentage = player->getHealth()->getCurrentHP() / player->getHealth()->getMaxHP();
	healthPercentage = glm::clamp(healthPercentage, 0.0f, 1.0f);

	float healthWidth = healthPercentage * healthOriginalWidth;

	float healthX = healthBaseX - (healthOriginalWidth * 0.5f) + (healthWidth * 0.5f);

	playerHealthBar->getTransform().setScale(glm::vec3(healthWidth, playerHealthBar->getTransform().getScale().y, playerHealthBar->getTransform().getScale().z));
	playerHealthBar->getTransform().setPosition(glm::vec3(healthX, playerHealthBar->getTransform().getPosition().y, playerHealthBar->getTransform().getPosition().z));

	//Wither Health Bar
	float totalHealthPercentage = (player->getHealth()->getCurrentHP() + player->getHealth()->getWitherHP()) / player->getHealth()->getMaxHP();
	totalHealthPercentage = glm::clamp(totalHealthPercentage, 0.0f, 1.0f);

	float witherWidth = totalHealthPercentage * healthOriginalWidth;

	float witherX = healthBaseX - (healthOriginalWidth * 0.5f) + (witherWidth * 0.5f);

	witherHealthBar->getTransform().setScale(glm::vec3(witherWidth, witherHealthBar->getTransform().getScale().y, witherHealthBar->getTransform().getScale().z));
	witherHealthBar->getTransform().setPosition(glm::vec3(witherX, witherHealthBar->getTransform().getPosition().y, witherHealthBar->getTransform().getPosition().z));

	//Ultimate Bar
	static float ultimateOriginalWidth = playerUltimateBar->getTransform().getScale().x;
	static float ultimateBaseX = playerUltimateBar->getTransform().getPosition().x;

	float ultimatePercentage = (player->getUltimateSlot() * 100.0f + player->getUltimateGauge()) / (player->getUltimateSlotMax() * 100.0f);
	ultimatePercentage = glm::clamp(ultimatePercentage, 0.0f, 1.0f);

	float ultimateWidth = ultimatePercentage * ultimateOriginalWidth;

	float ultimateX = ultimateBaseX - (ultimateOriginalWidth * 0.5f) + (ultimateWidth * 0.5f);

	playerUltimateBar->getTransform().setScale(glm::vec3(ultimateWidth, playerUltimateBar->getTransform().getScale().y, playerUltimateBar->getTransform().getScale().z));
	playerUltimateBar->getTransform().setPosition(glm::vec3(ultimateX, playerUltimateBar->getTransform().getPosition().y, playerUltimateBar->getTransform().getPosition().z));

	////Boss Health Bar
	//static float bossHealthOriginalWidth = bossHealthBar->getTransform().getScale().x;
	//static float bossHealthBaseX = bossHealthBar->getTransform().getPosition().x;

	//float bossHealthPercentage = ziz->getHealth()->getCurrentHP() / ziz->getHealth()->getMaxHP();
	////cout << ziz->getHealth()->getCurrentHP() << " " << ziz->getHealth()->getMaxHP() << endl;
	//bossHealthPercentage = glm::clamp(bossHealthPercentage, 0.0f, 1.0f);

	//float bossHealthWidth = bossHealthPercentage * bossHealthOriginalWidth;

	//float bossHealthX = bossHealthBaseX - (bossHealthOriginalWidth * 0.5f) + (bossHealthWidth * 0.5f);

	//bossHealthBar->getTransform().setScale(glm::vec3(bossHealthWidth, bossHealthBar->getTransform().getScale().y, bossHealthBar->getTransform().getScale().z));
	//bossHealthBar->getTransform().setPosition(glm::vec3(bossHealthX, 4.0f, 0.0f));

	if (player->getWeaponType() == WeaponType::Bow_) {
		//Overheat Bar
		static float overheatOriginalWidth = playerOverheatBar->getTransform().getScale().x;
		static float overheatBaseX = playerOverheatBar->getTransform().getPosition().x;

		float overheatPercentage = player->getBow()->getCurrentOverheat() / player->getBow()->getMaxOverheat();
		//float overheatPercentage = player->getBow()->getMaxOverheat() / player->getBow()->getMaxOverheat();
		overheatPercentage = glm::clamp(overheatPercentage, 0.0f, 1.0f);

		float overheatWidth = overheatPercentage * overheatOriginalWidth;

		float overheatX = overheatBaseX - (overheatOriginalWidth * 0.5f) + (overheatWidth * 0.5f);

		playerOverheatBar->getTransform().setScale(glm::vec3(overheatWidth, playerOverheatBar->getTransform().getScale().y, playerOverheatBar->getTransform().getScale().z));
		playerOverheatBar->getTransform().setPosition(glm::vec3(overheatX, playerOverheatBar->getTransform().getPosition().y, playerOverheatBar->getTransform().getPosition().z));
	}
}

void LevelMemTest::stateMachineUpdate(float dt) {
	/*if (ziz->getStateMachine()) {
		ziz->getStateMachine()->update(ziz, dt);
	}*/

	if (player->getStateMachine()) {
		player->getStateMachine()->update(player, dt);
		//cout << player->getTransform().getPosition().x << endl;
		if (player->getTransform().getPosition().x > 7.5f) {
			player->getTransform().setPosition(glm::vec3(7.5f, player->getTransform().getPosition().y, 0.0f));
		}
		if (player->getTransform().getPosition().x < -7.5f) {
			player->getTransform().setPosition(glm::vec3(-7.5f, player->getTransform().getPosition().y, 0.0f));
		}
	}
}

bool LevelMemTest::isPausing(float dt) {
	if (currentMenuState == MenuState::MAIN) { // isnt Pausing


		return false;
	}

	return true;
}

void LevelMemTest::changeMenuState(MenuState targetState) {
	if (targetState == currentMenuState || transitioning) return;

	selectedIndex = -1;

	nextMenuState = targetState;
	transitionTime = 0.0f;
	transitioning = true;
}

MenuState LevelMemTest::getMenuState() const {
	return currentMenuState;
}

void LevelMemTest::mouseUIHandling(int type, float x, float y) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	list<UIButton*>* currentList = nullptr;

	switch (currentMenuState) {
	case MenuState::OPTIONS:
		currentList = &optionsButtons;
		if (type == 1) {
			changeMenuState(MenuState::PAUSE);
		}
		break;
	case MenuState::PAUSE:
		currentList = &pauseButtons;
		break;
	case MenuState::AUDIO:
		currentList = &audioButtons;
		if (type == 1) {
			changeMenuState(MenuState::OPTIONS);
		}
		break;
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		if (type == 1) {
			changeMenuState(MenuState::OPTIONS);
		}
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
		if (type == 1) {
			changeMenuState(MenuState::OPTIONS);
		}
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		if (type == 1) {
			changeMenuState(MenuState::MAIN);
		}
		break;
	default:
		return;
	}


	if (selectedIndex >= 0 && selectedIndex < currentList->size()) {
		auto it = currentList->begin();
		std::advance(it, selectedIndex);

		UIButton* onButton = *it;

		if (onButton && onButton->getMouseOver()) {
			if (type == 0) {
				onButton->OnClick();
				if (onButton->getHandle()) {
					focusedHandle = *it;
				}
			}
		}
	}

	if (focusedHandle) {
		//cout << focusedHandle->getName() << endl;
		if (type == 2) {
			focusedHandle = nullptr;
		}

		if (type == 4) {

			SliderObject* handleSlider = focusedHandle->getSlider();

			if (handleSlider) {
				//cout << "has slider" << endl;
			}

			glm::vec2 gamePos = convertMouseToGameSpace(x, y);

			for (SliderObject* slider : slidersList) {

				if (focusedHandle->getSlider() == slider) {
					//cout << "Button's Slider: " << focusedHandle->getSlider()->getName() << " Slider:" << slider->getName() << endl;

					glm::vec3 handlePos = slider->getObject(2)->getTransform().getPosition(); // 2 = handle
					glm::vec3 bgPos = slider->getObject(0)->getTransform().getPosition(); // 0 = background

					float sliderLeft = bgPos.x - slider->getOriginalWidth().x * 0.5f;
					float sliderRight = bgPos.x + slider->getOriginalWidth().x * 0.5f;

					//cout << "Mouse Pos: " << gamePos.x << "," << gamePos.y << "Slider X Left:" << sliderLeft << ", Slider X Right:" << sliderRight << endl;


					if (gamePos.x <= sliderLeft) {
						slider->setValue(0.0f);
					}
					else if (gamePos.x >= sliderRight) {
						slider->setValue(1.0f);
					}
					else if (gamePos.x >= sliderLeft && gamePos.x <= sliderRight) {
						float newValue = (gamePos.x - sliderLeft) / (sliderRight - sliderLeft);
						slider->setValue(newValue);
					}
					slider->update(dt);
				}
			}
		}
	}
}

void LevelMemTest::keyboardUIHandling(char key) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();

	list<UIButton*>* currentList = nullptr;

	switch (currentMenuState) {
	case MenuState::MAIN:
		currentList = &mainButtons;
		break;
	case MenuState::OPTIONS:
		currentList = &optionsButtons;
		break;
	case MenuState::PAUSE:
		currentList = &pauseButtons;
		break;
	case MenuState::AUDIO:
		currentList = &audioButtons;
		break;
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		break;
	default:
		return;
	}

	/*UIButton* selectedButton = nullptr;

	if (selectedIndex >= 0 && selectedIndex < currentList->size()) {
		auto it = buttonsList.begin();
		std::advance(it, selectedIndex);

		selectedButton = *it;
	}*/

	/*switch (currentMenuState) {
	case MAIN:
		switch (key) {
		case 'w':
			changeSelection(-1);
			break;
		case 's':
			changeSelection(1);
			break;
		case 'S':
			if (selectedButton && selectedButton->getMouseOver()) {
				selectedButton->OnClick();
			}
			break;
		}
		break;
	case OPTIONS:

		break;
	case AUDIO:
		break;
	case CONTROLS:
		break;
	case CREDITS:
		break;
	default:
		break;
	}*/

	switch (key) {
	case 'a':
		if (isHolding == false) {
			if (focusedButton) {
				SliderObject* slider = focusedButton->getSlider();
				if (slider) {
					slider->setValue(slider->getValue() - 0.025f);
				}
			}
			isHolding = true;
		}

		if (isHolding == true) {
			holdButtonTimer += dt;
			if (holdButtonTimer >= holdButtonThreshold) {
				if (focusedButton) {
					SliderObject* slider = focusedButton->getSlider();
					if (slider) {
						slider->setValue(slider->getValue() - 0.005f);
					}
				}
			}
		}


		break;
	case 'd':

		if (isHolding == false) {
			if (focusedButton) {
				SliderObject* slider = focusedButton->getSlider();
				if (slider) {
					slider->setValue(slider->getValue() + 0.025f);
				}
			}
			isHolding = true;
		}

		if (isHolding == true) {
			holdButtonTimer += dt;
			if (holdButtonTimer >= holdButtonThreshold) {
				if (focusedButton) {
					SliderObject* slider = focusedButton->getSlider();
					if (slider) {
						slider->setValue(slider->getValue() + 0.005f);
					}
				}
			}
		}


		break;
	case 'w':
		changeSelection(-1);
		break;
	case 's':
		changeSelection(1);
		break;
	case 'q':
		if (currentMenuState == PAUSE) {
			changeMenuState(MenuState::MAIN);
		}
		else if (currentMenuState == OPTIONS) {
			changeMenuState(MenuState::PAUSE);
		}
		else if (currentMenuState == AUDIO) {
			changeMenuState(MenuState::OPTIONS);
		}
		else if (currentMenuState == CONTROLLER) {
			changeMenuState(MenuState::OPTIONS);
		}
		else if (currentMenuState == KEYBOARD) {
			changeMenuState(MenuState::OPTIONS);
		}
		else if (currentMenuState == CREDITS) {
			changeMenuState(MenuState::PAUSE);
		}
		break;
	case 'S':
		/*if (selectedButton && selectedButton->getMouseOver()) {
			selectedButton->OnClick();
		}*/

		if (focusedButton && focusedButton->getMouseOver()) {
			focusedButton->OnClick();
		}

		break;
	case 'I':
		if (isHolding == true) {
			isHolding = false;
		}
		if (holdButtonTimer > 0) {
			holdButtonTimer = 0;
		}
		break;
	}
}

glm::vec2 LevelMemTest::convertMouseToGameSpace(int mouseX, int mouseY) {
	int windowWidth = GameEngine::getInstance()->getWindowWidth();
	int windowHeight = GameEngine::getInstance()->getWindowHeight();

	const float targetAspect = 16.0f / 9.0f;
	float windowAspect = static_cast<float>(windowWidth) / windowHeight;

	float gameWidth = 16.0f;
	float gameHeight = 9.0f;

	float scale;
	float offsetX = 0;
	float offsetY = 0;

	if (windowAspect > targetAspect) {
		// Black bars on left/right
		scale = windowHeight / gameHeight;
		offsetX = (windowWidth - gameWidth * scale) / 2.0f;
	}
	else {
		// Black bars on top/bottom
		scale = windowWidth / gameWidth;
		offsetY = (windowHeight - gameHeight * scale) / 2.0f;
	}

	// Convert to normalized game coordinates
	float gameX = (mouseX - offsetX) / scale;
	float gameY = (mouseY - offsetY) / scale;

	// Flip Y if window origin is top-left but game origin is center
	gameY = gameHeight - gameY;

	// Shift origin to center
	gameX -= gameWidth / 2.0f;
	gameY -= gameHeight / 2.0f;

	return glm::vec2(gameX, gameY);
}

void LevelMemTest::changeSelection(int direction) {

	list<UIButton*>* currentList = nullptr;

	switch (currentMenuState) {
	case MenuState::OPTIONS:
		currentList = &optionsButtons;
		break;
	case MenuState::PAUSE:
		currentList = &pauseButtons;
		break;
	case MenuState::AUDIO:
		currentList = &audioButtons;
		break;
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		break;
	default:
		return;
	}


	if (!currentList || currentList->empty()) {
		return;
	}

	for (UIButton* btn : buttonsList) { // Deselect
		btn->setMouseOver(false);
	}

	if (selectedIndex == -1) {
		selectedIndex = 0;
	}
	else {
		selectedIndex += direction;
	}

	if (selectedIndex < 0) {
		selectedIndex = currentList->size() - 1;
	}
	else if (selectedIndex >= currentList->size()) {
		selectedIndex = 0;
	}

	auto it = currentList->begin();
	advance(it, selectedIndex);

	focusedButton = *it;

	if (focusedButton->getHandle()) {
		selectedIndex += direction;
	}

	if (selectedIndex < 0) {
		selectedIndex = currentList->size() - 1;
	}
	else if (selectedIndex >= currentList->size()) {
		selectedIndex = 0;
	}

	it = currentList->begin();
	advance(it, selectedIndex);

	focusedButton = *it;
	focusedButton->setMouseOver(true);
	//cout << focusedButton->getName() << endl;
}

void LevelMemTest::buttonsFree() {

	for (SliderObject*& slider : slidersList) {
		slider = nullptr;
	}

	for (UIButton*& button : buttonsList) {
		button = nullptr;
	}

	for (UIButton*& button : mainButtons) {
		button = nullptr;
	}

	for (UIButton*& button : pauseButtons) {
		button = nullptr;
	}

	for (UIButton*& button : optionsButtons) {
		button = nullptr;
	}

	for (UIButton*& button : audioButtons) {
		button = nullptr;
	}

	for (UIButton*& button : controllerButtons) {
		button = nullptr;
	}

	for (UIButton*& button : keyboardButtons) {
		button = nullptr;
	}

	for (UIButton*& button : creditsButton) {
		button = nullptr;
	}

	slidersList.clear();
	buttonsList.clear();
	mainButtons.clear();
	pauseButtons.clear();
	optionsButtons.clear();
	audioButtons.clear();
	controllerButtons.clear();
	keyboardButtons.clear();
	creditsButton.clear();
}

void LevelMemTest::UIUpdate() {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	bool anyButtonHovered = false;
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	list<UIButton*>* currentList = nullptr;

	switch (currentMenuState) {
	case MenuState::MAIN:
		currentList = &mainButtons;
		break;
	case MenuState::PAUSE:
		currentList = &pauseButtons;
		break;
	case MenuState::OPTIONS:
		currentList = &optionsButtons;
		break;
	case MenuState::AUDIO:
		currentList = &audioButtons;
		break;
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		break;
	default:
		return;
	}

	int index = 0;
	for (auto it = currentList->begin(); it != currentList->end(); ++it, ++index) {
		UIButton* button = *it;
		bool isHovered = button->isHovered(mouseX, mouseY);

		if (selectedIndex != index) {
			button->setMouseOver(isHovered);
		}

		if (isHovered) {
			hoveredIndex = index;
			selectedIndex = hoveredIndex;
			anyButtonHovered = true;
		}
	}

	// Handle control source switching
	if (anyButtonHovered) {
		controlByMouse = true;
	}
	else {
		hoveredIndex = -1;

		if (controlByMouse) {
			focusedButton = nullptr;
			controlByMouse = false;
			selectedIndex = -1;
		}
	}


	for (DrawableObject* obj : objectsList) {
		UIText* text = dynamic_cast<UIText*>(obj);
		if (text) {
			text->update(dt);
		}

		UIButton* button = dynamic_cast<UIButton*>(obj);
		if (button) {
			button->update(dt);
		}
	}

	if (transitioning) {
		transitionTime += dt;
		float t = transitionTime / transitionDuration;
		bool finish = false;
		if (t >= 1.0f) {
			t = 1.0f;
			finish = true;
		}

		for (DrawableObject* obj : objectsList) {
			MenuState objState = obj->getMenuState();
			vector<MenuState> objStateVec = obj->getMenuStateVec();

			if (obj->getMenuState() == MenuState::NONE && objStateVec.empty()) {
				continue;
			}

			if (find(objStateVec.begin(), objStateVec.end(), MenuState::IGNORE) != objStateVec.end()) {
				UIButton* button = dynamic_cast<UIButton*>(obj);
				if (button) {
					button->setEnable(true);
				}
				continue;
			}

			if (find(objStateVec.begin(), objStateVec.end(), MenuState::NONE) != objStateVec.end()) {
				obj->setAlpha(1.0f);
				continue;
			}

			bool inCurrent = objState == currentMenuState ||
				find(objStateVec.begin(), objStateVec.end(), currentMenuState) != objStateVec.end();
			bool inNext = objState == nextMenuState ||
				find(objStateVec.begin(), objStateVec.end(), nextMenuState) != objStateVec.end();

			if (inCurrent && inNext) { //If the object has many states.
				obj->setAlpha(obj->getMaximumAlpha());
			}
			else if (inCurrent) {
				float alpha = (1.0f - t) * obj->getMaximumAlpha();
				obj->setAlpha(alpha);
			}
			else if (inNext) {
				float alpha = t * obj->getMaximumAlpha();
				obj->setAlpha(alpha);
			}
			else {
				obj->setAlpha(0.0f);
			}
		}

		if (finish) {
			transitioning = false;
			currentMenuState = nextMenuState;
		}
	}
	else {
		for (DrawableObject* obj : objectsList) {
			MenuState objState = obj->getMenuState();
			vector<MenuState> objStateVec = obj->getMenuStateVec();

			if (obj->getMenuState() == MenuState::NONE && objStateVec.empty()) {
				continue;
			}

			if (find(objStateVec.begin(), objStateVec.end(), MenuState::IGNORE) != objStateVec.end()) {
				UIButton* button = dynamic_cast<UIButton*>(obj);
				if (button) {
					button->setEnable(true);
				}
				continue;
			}

			if (find(objStateVec.begin(), objStateVec.end(), MenuState::NONE) != objStateVec.end()) { //Doesn't affect by any states
				obj->setAlpha(obj->getMaximumAlpha());
				continue;
			}

			bool inCurrent = objState == currentMenuState ||
				find(objStateVec.begin(), objStateVec.end(), currentMenuState) != objStateVec.end();

			obj->setAlpha(inCurrent ? obj->getMaximumAlpha() : 0.0f);

			/*if (inCurrent) {
				cout << obj->getName() << "'s MenuState:" << obj->getMenuState() << " Alpha:" << obj->getAlpha() << endl;
				for (auto o : obj->getMenuStateVec()) {
					cout << o << endl;
				}
			}*/

			UIButton* button = dynamic_cast<UIButton*>(obj);

			if (button) {
				button->setEnable(inCurrent ? true : false);
			}
		}
	}

	for (SliderObject* obj : slidersList) {
		obj->update(dt);


		if (SoundManager::GetInstance()) {
			if (obj == masterSlider) {
				SoundManager::GetInstance()->setMasterVolume(masterSlider->getValue());
			}
			else if (obj == musicSlider) {
				SoundManager::GetInstance()->setMusicVolume(musicSlider->getValue());
			}
			else if (obj == sfxSlider) {
				SoundManager::GetInstance()->setSoundEffectVolume(sfxSlider->getValue());
			}
			else if (obj == ambientSlider) {
				SoundManager::GetInstance()->setAmbientVolume(ambientSlider->getValue());
			}
		}
	}

	InputManager* inputManager = GameEngine::getInstance()->getInputHandler();

	if (inputManager) {
		if (inputManager->getLastInput() == InputDevice::KEYBOARD) {
			kbOverlay->setDraw(true);
			controllerOverlay->setDraw(false);
		}
		else {
			kbOverlay->setDraw(false);
			controllerOverlay->setDraw(true);
		}
	}
}

void LevelMemTest::createPauseUI() {
	float audioSettingsOffsetY = 0.2f;

	TexturedObject* pauseBackground = new TexturedObject("pauseBackground");
	pauseBackground->setTexture("../Resource/Texture/UI/pauseMenu.png");
	pauseBackground->getTransform().setScale(glm::vec3(2.82f * 2.5f, 2.77f * 2.5f, 1.0f));
	pauseBackground->setMenuState(MenuState::PAUSE);
	pauseBackground->drawLayer = 999;
	objectsList.push_back(pauseBackground);

	TexturedObject* background2 = new TexturedObject("Background2");
	background2->setTexture("../Resource/Texture/newMainMenuBGOnly.png");
	background2->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background2->setMenuState(MenuState::AUDIO);
	background2->addMenuStateToVec(MenuState::CREDITS);
	//background2->addMenuStateToVec(MenuState::CONTROLLER);
	//background2->addMenuStateToVec(MenuState::KEYBOARD);
	background2->drawLayer = 999;
	objectsList.push_back(background2);

	TexturedObject* background3 = new TexturedObject("Background3");
	background3->setTexture("../Resource/Texture/MenuController.png");
	background3->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background3->setMenuState(MenuState::CONTROLLER);
	background3->drawLayer = 999;
	objectsList.push_back(background3);

	TexturedObject* background4 = new TexturedObject("Background4");
	background4->setTexture("../Resource/Texture/MenuMKB.png");
	background4->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background4->setMenuState(MenuState::KEYBOARD);
	background4->drawLayer = 999;
	objectsList.push_back(background4);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Overlays
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* overlayMKB = new TexturedObject("overlay MKB");
	overlayMKB->setTexture("../Resource/Texture/KB_Bundle.png");
	overlayMKB->getTransform().setPosition(glm::vec3(-4.8f, -4.0f, 1.0f));
	overlayMKB->getTransform().setScale(glm::vec3(2.382f * 2.2f, 0.277f * 2.2f, 1.0f));
	overlayMKB->setMenuState(MenuState::PAUSE);
	overlayMKB->addMenuStateToVec(MenuState::AUDIO);
	overlayMKB->addMenuStateToVec(MenuState::CREDITS);
	overlayMKB->addMenuStateToVec(MenuState::CONTROLLER);
	overlayMKB->addMenuStateToVec(MenuState::KEYBOARD);
	overlayMKB->drawLayer = 999;
	objectsList.push_back(overlayMKB);
	kbOverlay = overlayMKB;

	TexturedObject* overlayController = new TexturedObject("overlay Controller");
	overlayController->setTexture("../Resource/Texture/Controller_Bundle.png");
	overlayController->getTransform().setPosition(glm::vec3(-4.8f, -4.0f, 1.0f));
	overlayController->getTransform().setScale(glm::vec3(2.382f * 2.2f, 0.277f * 2.2f, 1.0f));
	overlayController->setMenuState(MenuState::PAUSE);
	overlayController->addMenuStateToVec(MenuState::AUDIO);
	overlayController->addMenuStateToVec(MenuState::CREDITS);
	overlayController->addMenuStateToVec(MenuState::CONTROLLER);
	overlayController->addMenuStateToVec(MenuState::KEYBOARD);
	overlayController->drawLayer = 999;
	objectsList.push_back(overlayController);
	controllerOverlay = overlayController;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Lines
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SimpleObject* line1 = new SimpleObject("Line1");
	line1->setColor(1.0f, 1.0f, 1.0f);
	line1->getTransform().setScale(glm::vec3(14.0f, 0.01f, 0.0f));
	line1->getTransform().setPosition(glm::vec3(0.0f, 3.3f, 0.0f));
	line1->setMenuState(MenuState::OPTIONS);
	line1->addMenuStateToVec(MenuState::AUDIO);
	line1->addMenuStateToVec(MenuState::CREDITS);
	line1->drawLayer = 999;
	objectsList.push_back(line1);

	SimpleObject* line2 = new SimpleObject("Line2");
	line2->setColor(1.0f, 1.0f, 1.0f);
	line2->getTransform().setScale(glm::vec3(14.0f, 0.01f, 0.0f));
	line2->getTransform().setPosition(glm::vec3(0.0f, -3.5f, 0.0f));
	line2->setMenuState(MenuState::OPTIONS);
	line2->addMenuStateToVec(MenuState::AUDIO);
	line2->addMenuStateToVec(MenuState::CREDITS);
	line2->drawLayer = 999;
	objectsList.push_back(line2);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Master Volume Slider
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SliderObject* masterVolumeSlider = new SliderObject("Master Volume Slider");
	masterVolumeSlider->setPosition(glm::vec3(-1.0f, 1.7f + audioSettingsOffsetY, 1.0f), -1);
	masterVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 0);
	masterVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 1);
	masterVolumeSlider->setScale(glm::vec3(0.35f, 0.35f, 1.0f), 2);
	masterVolumeSlider->setColor(glm::vec3(0.5f, 0.5f, 0.5f), -1);
	masterVolumeSlider->setColor(glm::vec3(0.75f, 0.75f, 0.75f), 1);
	masterVolumeSlider->setMenuState(MenuState::AUDIO);
	masterVolumeSlider->setValue(SoundManager::GetInstance()->getMasterVolume());
	for (DrawableObject* obj : masterVolumeSlider->getObjectsList()) {
		obj->drawLayer = 999;
		objectsList.push_back(obj);
	}
	UIButton* masterVolumeHandle = static_cast<UIButton*>(masterVolumeSlider->getObject(2));
	masterVolumeHandle->setTexture("../Resource/Texture/UI/SliderHandle.png");
	slidersList.push_back(masterVolumeSlider);
	buttonsList.push_back(static_cast<UIButton*>(masterVolumeSlider->getObject(2)));
	audioButtons.push_back(static_cast<UIButton*>(masterVolumeSlider->getObject(2)));
	masterSlider = masterVolumeSlider;

	//////////////////////////////////////

	UIText* masterVolumeText = new UIText("Master Volume Text");
	SDL_Color masterVolumeTextColor = { 255,255,255,255 };
	masterVolumeText->loadText("Master Volume", masterVolumeTextColor, 100);
	masterVolumeText->setText("Master Volume");
	masterVolumeText->setAlpha(1.0f);
	masterVolumeText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	masterVolumeText->getTransform().setPosition(glm::vec3(-3.65f, 2.1f + audioSettingsOffsetY, 0.0f));
	masterVolumeText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	masterVolumeText->addColliderComponent();
	masterVolumeText->setMenuState(MenuState::AUDIO);
	masterVolumeText->drawLayer = 999;
	/*masterVolumeText->setDrawCollider(true);
	masterVolumeText->setCanDrawColliderNew(true);*/
	objectsList.push_back(masterVolumeText);

	UIButton* masterVolumeButton = new UIButton("Master Volume Button");
	//masterVolumeButton->setTexture("../Resource/Texture/UI/SliderHandle.png");
	masterVolumeButton->getTransform().setPosition(glm::vec3(-4.5f, 2.35f + audioSettingsOffsetY, 0.0f));
	masterVolumeButton->getTransform().setScale(glm::vec3(2.35f, 0.35f, 0.0f));
	masterVolumeButton->addColliderComponent();
	//masterVolumeButton->setDrawCollider(true);
	//masterVolumeButton->setCanDrawColliderNew(true);
	masterVolumeButton->setDraw(false);
	masterVolumeButton->setLabel(masterVolumeText); // Link continueText
	masterVolumeButton->setMenuState(MenuState::AUDIO);
	masterVolumeButton->setSlider(masterVolumeSlider);
	masterVolumeButton->drawLayer = 999;
	objectsList.push_back(masterVolumeButton);
	buttonsList.push_back(masterVolumeButton);

	audioButtons.push_back(masterVolumeButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Music Volume Slider
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SliderObject* musicVolumeSlider = new SliderObject("Music Volume Slider");
	musicVolumeSlider->setPosition(glm::vec3(-1.0f, 0.2f + audioSettingsOffsetY, 1.0f), -1);
	musicVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 1);
	musicVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 0);
	musicVolumeSlider->setScale(glm::vec3(0.35f, 0.35f, 1.0f), 2);
	musicVolumeSlider->setColor(glm::vec3(0.5f, 0.5f, 0.5f), -1);
	musicVolumeSlider->setColor(glm::vec3(0.75f, 0.75f, 0.75f), 1);
	musicVolumeSlider->setMenuState(MenuState::AUDIO);
	musicVolumeSlider->setValue(SoundManager::GetInstance()->getMusicVolume());
	for (DrawableObject* obj : musicVolumeSlider->getObjectsList()) {
		obj->drawLayer = 999;
		objectsList.push_back(obj);
	}
	UIButton* musicVolumeHandle = static_cast<UIButton*>(musicVolumeSlider->getObject(2));
	musicVolumeHandle->setTexture("../Resource/Texture/UI/SliderHandle.png");
	slidersList.push_back(musicVolumeSlider);
	buttonsList.push_back(static_cast<UIButton*>(musicVolumeSlider->getObject(2)));
	audioButtons.push_back(static_cast<UIButton*>(musicVolumeSlider->getObject(2)));
	musicSlider = musicVolumeSlider;

	//////////////////////////////////////

	UIText* musicVolumeText = new UIText("Music Volume Text");
	SDL_Color musicVolumeTextColor = { 255,255,255,255 };
	musicVolumeText->loadText("Music Volume", musicVolumeTextColor, 100);
	musicVolumeText->setText("Music Volume");
	musicVolumeText->setAlpha(1.0f);
	musicVolumeText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	musicVolumeText->getTransform().setPosition(glm::vec3(-3.65f, 0.65f + audioSettingsOffsetY, 0.0f));
	musicVolumeText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	musicVolumeText->addColliderComponent();
	musicVolumeText->setMenuState(MenuState::AUDIO);
	musicVolumeText->drawLayer = 999;
	/*musicVolumeText->setDrawCollider(true);
	musicVolumeText->setCanDrawColliderNew(true);*/
	objectsList.push_back(musicVolumeText);

	UIButton* musicVolumeButton = new UIButton("Music Volume Button");
	//musicVolumeButton->setTexture("../Resource/Texture/UI/UIButton.png");
	musicVolumeButton->getTransform().setPosition(glm::vec3(-4.55f, 0.9f + audioSettingsOffsetY, 0.0f));
	musicVolumeButton->getTransform().setScale(glm::vec3(2.3f, 0.35f, 0.0f));
	musicVolumeButton->addColliderComponent();
	//musicVolumeButton->setDrawCollider(true);
	//musicVolumeButton->setCanDrawColliderNew(true);
	musicVolumeButton->setDraw(false);
	musicVolumeButton->setLabel(musicVolumeText); // Link continueText
	musicVolumeButton->setMenuState(MenuState::AUDIO);
	musicVolumeButton->setSlider(musicVolumeSlider);
	musicVolumeButton->drawLayer = 999;
	objectsList.push_back(musicVolumeButton);
	buttonsList.push_back(musicVolumeButton);

	audioButtons.push_back(musicVolumeButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Effect Volume Slider
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SliderObject* effectVolumeSlider = new SliderObject("Effect Volume Slider");
	effectVolumeSlider->setPosition(glm::vec3(-1.0f, -1.25f + audioSettingsOffsetY, 1.0f), -1);
	effectVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 1);
	effectVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 0);
	effectVolumeSlider->setScale(glm::vec3(0.35f, 0.35f, 1.0f), 2);
	effectVolumeSlider->setColor(glm::vec3(0.5f, 0.5f, 0.5f), -1);
	effectVolumeSlider->setColor(glm::vec3(0.75f, 0.75f, 0.75f), 1);
	effectVolumeSlider->setMenuState(MenuState::AUDIO);
	effectVolumeSlider->setValue(SoundManager::GetInstance()->getSoundEffectVolume());
	for (DrawableObject* obj : effectVolumeSlider->getObjectsList()) {
		obj->drawLayer = 999;
		objectsList.push_back(obj);
	}
	UIButton* effectVolumeHandle = static_cast<UIButton*>(effectVolumeSlider->getObject(2));
	effectVolumeHandle->setTexture("../Resource/Texture/UI/SliderHandle.png");
	slidersList.push_back(effectVolumeSlider);
	buttonsList.push_back(static_cast<UIButton*>(effectVolumeSlider->getObject(2)));
	audioButtons.push_back(static_cast<UIButton*>(effectVolumeSlider->getObject(2)));
	sfxSlider = effectVolumeSlider;

	//////////////////////////////////////

	UIText* effectVolumeText = new UIText("Effect Volume Text");
	SDL_Color effectVolumeTextColor = { 255,255,255,255 };
	effectVolumeText->loadText("Effect Volume", effectVolumeTextColor, 100);
	effectVolumeText->setText("Effect Volume");
	effectVolumeText->setAlpha(1.0f);
	effectVolumeText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	effectVolumeText->getTransform().setPosition(glm::vec3(-3.65f, -0.8f + audioSettingsOffsetY, 0.0f));
	effectVolumeText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	effectVolumeText->addColliderComponent();
	effectVolumeText->setMenuState(MenuState::AUDIO);
	effectVolumeText->drawLayer = 999;
	/*effectVolumeText->setDrawCollider(true);
	effectVolumeText->setCanDrawColliderNew(true);*/
	objectsList.push_back(effectVolumeText);

	UIButton* effectVolumeButton = new UIButton("Effect Volume Button");
	//effectVolumeButton->setTexture("../Resource/Texture/UI/UIButton.png");
	effectVolumeButton->getTransform().setPosition(glm::vec3(-4.6f, -0.55f + audioSettingsOffsetY, 0.0f));
	effectVolumeButton->getTransform().setScale(glm::vec3(2.15f, 0.35f, 0.0f));
	effectVolumeButton->addColliderComponent();
	//effectVolumeButton->setDrawCollider(true);
	//effectVolumeButton->setCanDrawColliderNew(true);
	effectVolumeButton->setDraw(false);
	effectVolumeButton->setLabel(effectVolumeText); // Link continueText
	effectVolumeButton->setMenuState(MenuState::AUDIO);
	effectVolumeButton->setSlider(effectVolumeSlider);
	effectVolumeButton->drawLayer = 999;
	objectsList.push_back(effectVolumeButton);
	buttonsList.push_back(effectVolumeButton);

	audioButtons.push_back(effectVolumeButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Ambient Volume Slider
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SliderObject* ambientVolumeSlider = new SliderObject("Ambient Volume Slider");
	ambientVolumeSlider->setPosition(glm::vec3(-1.0f, -2.68f + audioSettingsOffsetY, 1.0f), -1);
	ambientVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 1);
	ambientVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 0);
	ambientVolumeSlider->setScale(glm::vec3(0.35f, 0.35f, 1.0f), 2);
	ambientVolumeSlider->setColor(glm::vec3(0.5f, 0.5f, 0.5f), -1);
	ambientVolumeSlider->setColor(glm::vec3(0.75f, 0.75f, 0.75f), 1);
	ambientVolumeSlider->setMenuState(MenuState::AUDIO);
	ambientVolumeSlider->setValue(SoundManager::GetInstance()->getAmbientVolume());
	for (DrawableObject* obj : ambientVolumeSlider->getObjectsList()) {
		obj->drawLayer = 999;
		objectsList.push_back(obj);
	}
	UIButton* ambientVolumeHandle = static_cast<UIButton*>(ambientVolumeSlider->getObject(2));
	ambientVolumeHandle->setTexture("../Resource/Texture/UI/SliderHandle.png");
	slidersList.push_back(ambientVolumeSlider);
	buttonsList.push_back(static_cast<UIButton*>(ambientVolumeSlider->getObject(2)));
	audioButtons.push_back(static_cast<UIButton*>(ambientVolumeSlider->getObject(2)));
	ambientSlider = ambientVolumeSlider;

	//////////////////////////////////////

	UIText* ambientVolumeText = new UIText("Ambient Volume Text");
	SDL_Color ambientVolumeTextColor = { 255,255,255,255 };
	ambientVolumeText->loadText("Ambient Volume", ambientVolumeTextColor, 100);
	ambientVolumeText->setText("Ambient Volume");
	ambientVolumeText->setAlpha(1.0f);
	ambientVolumeText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	ambientVolumeText->getTransform().setPosition(glm::vec3(-3.65f, -2.25f + audioSettingsOffsetY, 0.0f));
	ambientVolumeText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	ambientVolumeText->addColliderComponent();
	ambientVolumeText->setMenuState(MenuState::AUDIO);
	ambientVolumeText->drawLayer = 999;
	/*ambientVolumeText->setDrawCollider(true);
	ambientVolumeText->setCanDrawColliderNew(true);*/
	objectsList.push_back(ambientVolumeText);

	UIButton* ambientVolumeButton = new UIButton("Ambient Volume Button");
	//ambientVolumeButton->setTexture("../Resource/Texture/UI/UIButton.png");
	ambientVolumeButton->getTransform().setPosition(glm::vec3(-4.35f, -2.0f + audioSettingsOffsetY, 0.0f));
	ambientVolumeButton->getTransform().setScale(glm::vec3(2.65f, 0.35f, 0.0f));
	ambientVolumeButton->addColliderComponent();
	//ambientVolumeButton->setDrawCollider(true);
	//ambientVolumeButton->setCanDrawColliderNew(true);
	ambientVolumeButton->setDraw(false);
	ambientVolumeButton->setLabel(ambientVolumeText); // Link continueText
	ambientVolumeButton->setMenuState(MenuState::AUDIO);
	ambientVolumeButton->setSlider(ambientVolumeSlider);
	ambientVolumeButton->drawLayer = 999;
	objectsList.push_back(ambientVolumeButton);
	buttonsList.push_back(ambientVolumeButton);

	audioButtons.push_back(ambientVolumeButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Continue Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* continueText = new UIText("Continue Text");
	SDL_Color continueTextColor = { 255,255,255,255 };
	continueText->loadText("Continue", continueTextColor, 100);
	continueText->setText("Continue");
	continueText->setAlpha(1.0f);
	continueText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	continueText->getTransform().setPosition(glm::vec3(0.25f, 0.0f - 0.6f, 0.0f));
	continueText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	continueText->addColliderComponent();
	continueText->setMenuState(MenuState::PAUSE);
	continueText->drawLayer = 999;
	/*continueText->setDrawCollider(true);
	continueText->setCanDrawColliderNew(true);*/
	objectsList.push_back(continueText);

	UIButton* continueButton = new UIButton("Continue Button");
	//continueButton->setTexture("../Resource/Texture/UI/UIButton.png");
	continueButton->getTransform().setPosition(glm::vec3(0.0f, 0.25f - 0.6f, 0.0f));
	continueButton->getTransform().setScale(glm::vec3(1.6f, 0.35f, 0.0f));
	continueButton->addColliderComponent();
	continueButton->setDrawCollider(true);
	continueButton->setCanDrawColliderNew(false);
	continueButton->setDraw(false);
	continueButton->setLabel(continueText); // Link continueText
	continueButton->setMenuState(MenuState::PAUSE);
	continueButton->drawLayer = 999;
	objectsList.push_back(continueButton);
	buttonsList.push_back(continueButton);

	pauseButtons.push_back(continueButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Settings Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* settingsText = new UIText("Settings Text");
	SDL_Color settingsTextColor = { 255,255,255,255 };
	settingsText->loadText("Settings", settingsTextColor, 100);
	settingsText->setText("Settings");
	settingsText->setAlpha(1.0f);
	settingsText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	settingsText->getTransform().setPosition(glm::vec3(0.41f, -1.05f - 0.8f, 0.0f));
	settingsText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	settingsText->addColliderComponent();
	settingsText->setMenuState(MenuState::PAUSE);
	settingsText->drawLayer = 999;
	/*settingsText->setDrawCollider(true);
	settingsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(settingsText);

	UIButton* settingsButton = new UIButton("Settings Button");
	//settingsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	settingsButton->getTransform().setPosition(glm::vec3(0.0f, -0.81f - 0.8f, 0.0f));
	settingsButton->getTransform().setScale(glm::vec3(1.3f, 0.35f, 0.0f));
	settingsButton->addColliderComponent();
	settingsButton->setDrawCollider(true);
	settingsButton->setCanDrawColliderNew(true);
	settingsButton->setDraw(false);
	settingsButton->setLabel(settingsText); // Link playText
	settingsButton->setMenuState(MenuState::PAUSE);
	settingsButton->drawLayer = 999;
	settingsButton->setFunction([this]() { changeMenuState(MenuState::OPTIONS);});
	objectsList.push_back(settingsButton);
	buttonsList.push_back(settingsButton);

	pauseButtons.push_back(settingsButton);
}