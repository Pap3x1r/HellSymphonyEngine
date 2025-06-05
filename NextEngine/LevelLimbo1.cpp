#include "LevelLimbo1.h"
#include "CollisionHandler.h"
#include "Bow.h"
#include "ZizGroundSlamState.h"
#include "GameEngine.h" // Include GameEngine header
#include "GLRenderer.h" // Include GLRenderer header
#include <iostream>
#include <random>
#include <fstream>
using namespace std;




void LevelLimbo1::levelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->loadData();
	GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

	SquareBorderMesh* border = new SquareBorderMesh();
	border->loadData();
	GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);
}

void LevelLimbo1::levelInit() {

	currentControlType = ControlType::keyboard;

	TexturedObject* background = new TexturedObject("background");
	background->setTexture("../Resource/Texture/Limbo_FirstHalf-NoLight.png");
	background->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	objectsList.push_back(background);

	TexturedObject* background2 = new TexturedObject("background");
	background2->setTexture("../Resource/Texture/Limbo_Lightray.png");
	background2->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background2->drawLayer = 1;
	objectsList.push_back(background2);

	InteractableObject* vergil_ = new InteractableObject("Vergil");
	vergil_->getTransform().setScale(glm::vec3(-3.25, 3.25f * 1, 1));
	vergil_->getTransform().setPosition(glm::vec3(-3.3f, -2.05f, 1));
	vergil_->addColliderComponent();
	vergil_->getColliderComponent()->setTrigger(true);
	vergil_->getColliderComponent()->setDimension(0.1f, 0.4f);
	vergil_->initAnimation(8, 1);
	vergil_->getAnimationComponent()->addState("idle", 0, 8);
	vergil_->getAnimationComponent()->addState("highlight", 0, 8);
	objectsList.push_back(vergil_);
	vergil = vergil_;

	InteractableObject* bowStatue_ = new InteractableObject("Vergil");
	bowStatue_->getTransform().setScale(glm::vec3(3.25, 3.25f * 1, 1));
	bowStatue_->getTransform().setPosition(glm::vec3(1.4f, -1.5f, 1));
	bowStatue_->addColliderComponent();
	bowStatue_->getColliderComponent()->setTrigger(true);
	bowStatue_->getColliderComponent()->setDimension(0.1f, 0.4f);
	bowStatue_->getColliderComponent()->getTransform().setPosition(glm::vec3(0.0f, -0.5f, 1));
	objectsList.push_back(bowStatue_);
	bowStatue = bowStatue_;

	InteractableObject* swordStatue_ = new InteractableObject("Vergil");
	swordStatue_->getTransform().setScale(glm::vec3(3.25, 3.25f * 1, 1));
	swordStatue_->getTransform().setPosition(glm::vec3(3.4f, -1.5f, 1));
	swordStatue_->addColliderComponent();
	swordStatue_->getColliderComponent()->setTrigger(true);
	swordStatue_->getColliderComponent()->setDimension(0.1f, 0.4f);
	swordStatue_->getColliderComponent()->getTransform().setPosition(glm::vec3(0.0f, -0.5f, 1));
	objectsList.push_back(swordStatue_);
	swordStatue = swordStatue_;

	InteractableObject* shieldStatue_ = new InteractableObject("Vergil");
	shieldStatue_->getTransform().setScale(glm::vec3(3.25, 3.25f * 1, 1));
	shieldStatue_->getTransform().setPosition(glm::vec3(2.4f, -1.5f, 1));
	shieldStatue_->addColliderComponent();
	shieldStatue_->getColliderComponent()->setTrigger(true);
	shieldStatue_->getColliderComponent()->setDimension(0.1f, 0.4f);
	shieldStatue_->getColliderComponent()->getTransform().setPosition(glm::vec3(0.0f, -0.5f, 1));
	objectsList.push_back(shieldStatue_);
	shieldStatue = shieldStatue_;


	Player* player_ = GameEngine::getInstance()->loadPlayerData("../Resource/Saves/PlayerData/playerData.txt");
	objectsList.push_back(player_);
	player = player_;
	player->setLevel(this);

	if (GameEngine::getInstance()->playerPos != glm::vec3(0.0f)) {
		player->getTransform().setPosition(GameEngine::getInstance()->playerPos);
		player->setFacingRight(false);
		GameEngine::getInstance()->playerPos = glm::vec3(0.0f);
	}
	else {
		SoundManager::GetInstance()->StopAllSounds();
		SoundManager::GetInstance()->PlayMusic("Limbo-SoundTrack");
		player->getTransform().setPosition(glm::vec3(-5.8, -0.8f, 0.0f));
	}
	
	objectsList.push_back(player->getGroundChecker());

	if (GameEngine::getInstance()->isNewGame == true) {
		player->setWeaponType(GameEngine::getInstance()->loadPlayerWeaponType("../Resource/Saves/PlayerData/playerWeaponTypeData.txt", true));
		GameEngine::getInstance()->isNewGame = false;
	}
	else {
		player->setWeaponType(GameEngine::getInstance()->loadPlayerWeaponType("../Resource/Saves/PlayerData/playerWeaponTypeData.txt", false));
	}
	
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

	SimpleObject* floor = new SimpleObject();
	floor->getTransform().setPosition(glm::vec3(0.0f, -4.15f, 0.0f));
	floor->getTransform().setScale(glm::vec3(18.0f, 2.0f, 0.0f));
	floor->addColliderComponent();
	floor->setName("Floor");
	floor->setDrawCollider(true);
	floor->setCanDrawColliderNew(false);
	floor->setDraw(false);
	objectsList.push_back(floor);

	//Overheat
	TexturedObject* overheatBarBackground = new TexturedObject();
	overheatBarBackground->setTexture("../Resource/Texture/UI/Bow/Overheat_Empty_BG.png");
	overheatBarBackground->getTransform().setScale(glm::vec3(1.37f * 2.75f, 0.02f * 4.5f, 1.0f));
	overheatBarBackground->getTransform().setPosition(glm::vec3(-4.1f, -3.55f, 0.0f));
	overheatBarBackground->drawLayer = 10;
	objectsList.push_back(overheatBarBackground);
	playerOverheatBarBackground = overheatBarBackground;

	SimpleObject* overheatBar = new SimpleObject();
	overheatBar->setColor(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f);
	overheatBar->getTransform().setScale(glm::vec3(3.665f, 0.08f, 0.0f));
	overheatBar->getTransform().setPosition(glm::vec3(-4.1f, -3.55f, 0.0f));
	overheatBar->drawLayer = 10;
	objectsList.push_back(overheatBar);
	playerOverheatBar = overheatBar;

	TexturedObject* overheatBarFrame = new TexturedObject();
	overheatBarFrame->setTexture("../Resource/Texture/UI/Bow/Overheat_Frame.png");
	overheatBarFrame->getTransform().setScale(glm::vec3(1.37f * 2.75f, 0.02f * 4.5f, 1.0f));
	overheatBarFrame->getTransform().setPosition(glm::vec3(-4.1f, -3.55f, 0.0f));
	overheatBarFrame->drawLayer = 10;
	objectsList.push_back(overheatBarFrame);
	playerOverheatBarFrame = overheatBarFrame;

	//Health & Ult UI
	//cout << "Init Level" << endl;
	TexturedObject* healthBarBackground = new TexturedObject();
	healthBarBackground->setTexture("../Resource/Texture/UI/Healthbar_BG.png");
	healthBarBackground->getTransform().setScale(glm::vec3(2.42f * 2.5f, 0.5f * 2.5f, 1.0f));
	healthBarBackground->getTransform().setPosition(glm::vec3(-5.0f, -4.0f, 0.0f));
	healthBarBackground->drawLayer = 10;
	objectsList.push_back(healthBarBackground);

	SimpleObject* witherHealthBar_ = new SimpleObject();
	witherHealthBar_->setColor(106.0f / 255.0f, 109.0f / 255.0f, 115.0f / 255.0f);
	witherHealthBar_->getTransform().setScale(glm::vec3(5.375f, 0.23f, 0.0f));
	witherHealthBar_->getTransform().setPosition(glm::vec3(-5.05f, -3.95f, 0.0f));
	witherHealthBar_->drawLayer = 10;
	objectsList.push_back(witherHealthBar_);
	witherHealthBar = witherHealthBar_;

	SimpleObject* healthBar = new SimpleObject();
	healthBar->setColor(1.0f, 0.0f, 0.0f);
	healthBar->getTransform().setScale(glm::vec3(5.375f, 0.23f, 0.0f));
	healthBar->getTransform().setPosition(glm::vec3(-5.05f, -3.95f, 0.0f));
	healthBar->drawLayer = 10;
	objectsList.push_back(healthBar);
	playerHealthBar = healthBar;

	SimpleObject* ultimateBar = new SimpleObject();
	ultimateBar->setColor(235.0f / 255.0f, 168.0f / 255.0f, 52.0f / 255.0f);
	ultimateBar->getTransform().setScale(glm::vec3(3.18f, 0.25f, 0.0f));
	ultimateBar->getTransform().setPosition(glm::vec3(-6.165f, -4.225f, 0.0f));
	ultimateBar->drawLayer = 10;
	objectsList.push_back(ultimateBar);
	playerUltimateBar = ultimateBar;

	TexturedObject* healthBarFrame = new TexturedObject();
	healthBarFrame->setTexture("../Resource/Texture/UI/Healthbar_Frame.png");
	healthBarFrame->getTransform().setScale(glm::vec3(2.42f * 2.5f, 0.5f * 2.5f, 1.0f));
	healthBarFrame->getTransform().setPosition(glm::vec3(-5.0f, -4.0f, 0.0f));
	healthBarFrame->drawLayer = 10;
	objectsList.push_back(healthBarFrame);


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

	//GameEngine::getInstance()->freezeGameForSecond(0.6f);
	inputManager = GameEngine::getInstance()->getInputHandler();
}

void LevelLimbo1::levelUpdate() {
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

	if (player) {
		player->updateShake(dt);
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

			if (button->getMouseOver()) {
				button->setMouseOver(false);
			}
		}

		InteractableObject* interact = dynamic_cast<InteractableObject*>(obj);
		if (interact) {
			interact->selfUpdate(dt);

			
		}
	}

	updateUIBar();

	player->selfUpdate(playerDT);
	player->getSword()->update(playerDT, player);
	player->getBow()->update(playerDT, player);
	player->getShield()->update(playerDT, player);

	player->getAnimationComponent()->updateCurrentState(playerDT);

	vergil->selfUpdate(playerDT);
	bowStatue->selfUpdate(playerDT);
	if (bowStatue->getPlayerInside()) {
		if (bowStatue2) {
			bowStatue2->setDraw(true);
			if (GameEngine::getInstance()->getInputHandler()->getLastInput() == InputDevice::CONTROLLER) {
				bowStatue2->setTexture("../Resource/Texture/UI/RB.png");
			}
			else {
				bowStatue2->setTexture("../Resource/Texture/UI/E.png");
			}
		}

		bowStatue->setTexture("../Resource/Texture/Interactables/Bow_Guy-Outlined.png");
	}
	else {
		bowStatue->setTexture("../Resource/Texture/Interactables/Bow_Guy.png");
		bowStatue2->setDraw(false);
	}

	swordStatue->selfUpdate(playerDT);
	if (swordStatue->getPlayerInside()) {
		if (swordStatue2) {
			swordStatue2->setDraw(true);
			if (GameEngine::getInstance()->getInputHandler()->getLastInput() == InputDevice::CONTROLLER) {
				swordStatue2->setTexture("../Resource/Texture/UI/RB.png");
			}
			else {
				swordStatue2->setTexture("../Resource/Texture/UI/E.png");
			}
		}
		swordStatue->setTexture("../Resource/Texture/Interactables/Sword_Guy-Outlined.png");
	}
	else {
		swordStatue->setTexture("../Resource/Texture/Interactables/Sword_Guy.png");
		swordStatue2->setDraw(false);
	}

	shieldStatue->selfUpdate(playerDT);
	if (shieldStatue->getPlayerInside()) {
		if (shieldStatue2) {
			shieldStatue2->setDraw(true);
			if (GameEngine::getInstance()->getInputHandler()->getLastInput() == InputDevice::CONTROLLER) {
				shieldStatue2->setTexture("../Resource/Texture/UI/RB.png");
			}
			else {
				shieldStatue2->setTexture("../Resource/Texture/UI/E.png");
			}
		}
		shieldStatue->setTexture("../Resource/Texture/Interactables/Shield_Guy-Outlined.png");
	}
	else {
		shieldStatue->setTexture("../Resource/Texture/Interactables/Shield_Guy.png");
		shieldStatue2->setDraw(false);
	}

	//handleObjectCollision(objectsList);

}

void LevelLimbo1::levelDraw() {
	GameEngine::getInstance()->render(objectsList);
	//cout << "Draw Level" << endl;
}

void LevelLimbo1::levelFree() {
	//savePlayerData(player, "../Resource/Saves/PlayerData/playerData.txt");

	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	buttonsFree();
}

void LevelLimbo1::levelUnload() {
	GameEngine::getInstance()->clearMesh();
	//cout << "Unload Level" << endl;
}

void LevelLimbo1::isReceivingNoInputs() {
	cout << "not receieving input" << endl;

	if (player->getIsGrounded()) {
		player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
	}
	player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
}

void LevelLimbo1::switchControlType(ControlType ct) {
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

void LevelLimbo1::handleKey(char key) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float speed = 20.0f;
	speed *= dt;

	bool playerIsMoving = false;

	if (currentMenuState != MenuState::MAIN) {
		if (key == 'E') {
			changeMenuState(MenuState::MAIN);
		}
		keyboardUIHandling(key);
		return;
	}

	if (key == 'E') {
		changeMenuState(MenuState::PAUSE);
	}

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
		SoundManager::GetInstance()->LoadMusic("LimboMusic", "../Resource/Audio/Music/Limbo-Soundtrack.mp3", false);
		SoundManager::GetInstance()->PlayMusic("LimboMusic", true);
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

			if (player->getIsGrounded()) {
				player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
			}
		}

		break;
	case 'e':
		if (vergil->getPlayerInside()) {

		}

		if (bowStatue->getPlayerInside()) {
			player->setWeaponType(WeaponType::Bow_);
			player->getStateMachine()->changeState(player->getStateMachine()->getCurrentState(), player, true);
			SoundManager::GetInstance()->PlaySFX("Misc-ChooseWeapon");
		}

		if (swordStatue->getPlayerInside()) {
			player->setWeaponType(WeaponType::Sword_);
			player->getStateMachine()->changeState(player->getStateMachine()->getCurrentState(), player, true);
			SoundManager::GetInstance()->PlaySFX("Misc-ChooseWeapon");
		}

		if (shieldStatue->getPlayerInside()) {
			player->setWeaponType(WeaponType::Shield_);
			player->getStateMachine()->changeState(player->getStateMachine()->getCurrentState(), player, true);
			SoundManager::GetInstance()->PlaySFX("Misc-ChooseWeapon");
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
				player->getStateMachine()->changeState(PlayerDashState::getInstance(), player);
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

void LevelLimbo1::handleControllerButton(SDL_GameControllerButton button) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float speed = 20.0f;
	speed *= dt;

	if (currentMenuState != MenuState::MAIN) {
		if (button == SDL_CONTROLLER_BUTTON_START) {
			changeMenuState(MenuState::MAIN);
		}

		controllerUIHandling(button);
		return;
	}

	if (button == SDL_CONTROLLER_BUTTON_START) {
		changeMenuState(MenuState::PAUSE);
	}

	bool playerIsMoving = false;
	if (player->getIsDead()) return;

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
				player->getStateMachine()->changeState(PlayerDashState::getInstance(), player);
			}
		}

		break;
	case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:

		if (bowStatue->getPlayerInside()) {
			player->setWeaponType(WeaponType::Bow_);
			player->getStateMachine()->changeState(player->getStateMachine()->getCurrentState(), player, true);
			SoundManager::GetInstance()->PlaySFX("Misc-ChooseWeapon");
		}

		if (swordStatue->getPlayerInside()) {
			player->setWeaponType(WeaponType::Sword_);
			player->getStateMachine()->changeState(player->getStateMachine()->getCurrentState(), player, true);
			SoundManager::GetInstance()->PlaySFX("Misc-ChooseWeapon");
		}

		if (shieldStatue->getPlayerInside()) {
			player->setWeaponType(WeaponType::Shield_);
			player->getStateMachine()->changeState(player->getStateMachine()->getCurrentState(), player, true);
			SoundManager::GetInstance()->PlaySFX("Misc-ChooseWeapon");
		}

		break;
	default:
		break;
	}
}


void LevelLimbo1::handleMouse(int type, int x, int y) {
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

void LevelLimbo1::handleAnalogStick(int type, char key) {
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
	else if (type == 5) {
		if (key == '6') {
			if (player->getIsGrounded() == false) return;
			if (player->getIsDashing() == true) return;
			if (player->getIsStunned() == true) return;
			if (player->getSword()->getInChainAttack() || player->getShield()->getInChainAttack() || player->getShield()->getIsHolding() || player->getBow()->getIsShooting()) { //Prevent returning back to idle
				return;
			}
			switchControlType(controller);
			//ziz->interruptIntoPhase();
			playerUltimateInput();
		}
	}
}

void LevelLimbo1::addObject(DrawableObject* obj) {
	objectsList.push_back(obj);
}

void LevelLimbo1::addPlayerToDebug(Player* player) {

}

void LevelLimbo1::createSkillsIcon() {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Bow Skills Icon
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* bowSmallUltIconOff_ = new TexturedObject("Bow Small Ultimate Icon Off");
	bowSmallUltIconOff_->setTexture("../Resource/Texture/UI/Skills/Bow_Min_Off.png");
	bowSmallUltIconOff_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	bowSmallUltIconOff_->getTransform().setPosition(glm::vec3(-7.4f, -3.375f, 1.0f));
	bowSmallUltIconOff_->drawLayer = 10;
	objectsList.push_back(bowSmallUltIconOff_);
	bowSmallUltIconOff = bowSmallUltIconOff_;

	TexturedObject* bowSmallUltIconOn_ = new TexturedObject("Bow Small Ultimate Icon On");
	bowSmallUltIconOn_->setTexture("../Resource/Texture/UI/Skills/Bow_Min_On.png");
	bowSmallUltIconOn_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	bowSmallUltIconOn_->getTransform().setPosition(glm::vec3(-7.4f, -3.375f, 1.0f));
	bowSmallUltIconOn_->drawLayer = 10;
	objectsList.push_back(bowSmallUltIconOn_);
	bowSmallUltIconOn = bowSmallUltIconOn_;

	TexturedObject* bowBigUltIconOff_ = new TexturedObject("Bow Big Ultimate Icon Off");
	bowBigUltIconOff_->setTexture("../Resource/Texture/UI/Skills/Bow_Max_Off.png");
	bowBigUltIconOff_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	bowBigUltIconOff_->getTransform().setPosition(glm::vec3(-6.55f, -3.375f, 1.0f));
	bowBigUltIconOff_->drawLayer = 10;
	objectsList.push_back(bowBigUltIconOff_);
	bowBigUltIconOff = bowBigUltIconOff_;

	TexturedObject* bowBigUltIconOn_ = new TexturedObject("Bow Big Ultimate Icon On");
	bowBigUltIconOn_->setTexture("../Resource/Texture/UI/Skills/Bow_Max_On.png");
	bowBigUltIconOn_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	bowBigUltIconOn_->getTransform().setPosition(glm::vec3(-6.55f, -3.375f, 1.0f));
	bowBigUltIconOn_->drawLayer = 10;
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
	swordSmallUltIconOff_->drawLayer = 10;
	objectsList.push_back(swordSmallUltIconOff_);
	swordSmallUltIconOff = swordSmallUltIconOff_;

	TexturedObject* swordSmallUltIconOn_ = new TexturedObject("Sword Small Ultimate Icon On");
	swordSmallUltIconOn_->setTexture("../Resource/Texture/UI/Skills/Sword_Min_On.png");
	swordSmallUltIconOn_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	swordSmallUltIconOn_->getTransform().setPosition(glm::vec3(-7.4f, -3.375f, 1.0f));
	swordSmallUltIconOn_->drawLayer = 10;
	objectsList.push_back(swordSmallUltIconOn_);
	swordSmallUltIconOn = swordSmallUltIconOn_;

	TexturedObject* swordBigUltIconOff_ = new TexturedObject("Sword Big Ultimate Icon Off");
	swordBigUltIconOff_->setTexture("../Resource/Texture/UI/Skills/Sword_Max_Off.png");
	swordBigUltIconOff_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	swordBigUltIconOff_->getTransform().setPosition(glm::vec3(-6.55f, -3.375f, 1.0f));
	swordBigUltIconOff_->drawLayer = 10;
	objectsList.push_back(swordBigUltIconOff_);
	swordBigUltIconOff = swordBigUltIconOff_;

	TexturedObject* swordBigUltIconOn_ = new TexturedObject("Sword Big Ultimate Icon On");
	swordBigUltIconOn_->setTexture("../Resource/Texture/UI/Skills/Sword_Max_On.png");
	swordBigUltIconOn_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	swordBigUltIconOn_->getTransform().setPosition(glm::vec3(-6.55f, -3.375f, 1.0f));
	swordBigUltIconOn_->drawLayer = 10;
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
	shieldSmallUltIconOff_->drawLayer = 10;
	objectsList.push_back(shieldSmallUltIconOff_);
	shieldSmallUltIconOff = shieldSmallUltIconOff_;

	TexturedObject* shieldSmallUltIconOn_ = new TexturedObject("Shield Small Ultimate Icon On");
	shieldSmallUltIconOn_->setTexture("../Resource/Texture/UI/Skills/Shield_Min_On.png");
	shieldSmallUltIconOn_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	shieldSmallUltIconOn_->getTransform().setPosition(glm::vec3(-7.4f, -3.375f, 1.0f));
	shieldSmallUltIconOn_->drawLayer = 10;
	objectsList.push_back(shieldSmallUltIconOn_);
	shieldSmallUltIconOn = shieldSmallUltIconOn_;

	TexturedObject* shieldBigUltIconOff_ = new TexturedObject("Shield Big Ultimate Icon Off");
	shieldBigUltIconOff_->setTexture("../Resource/Texture/UI/Skills/Shield_Max_Off.png");
	shieldBigUltIconOff_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	shieldBigUltIconOff_->getTransform().setPosition(glm::vec3(-6.55f, -3.375f, 1.0f));
	shieldBigUltIconOff_->drawLayer = 10;
	objectsList.push_back(shieldBigUltIconOff_);
	shieldBigUltIconOff = shieldBigUltIconOff_;

	TexturedObject* shieldBigUltIconOn_ = new TexturedObject("Shield Big Ultimate Icon On");
	shieldBigUltIconOn_->setTexture("../Resource/Texture/UI/Skills/Shield_Max_On.png");
	shieldBigUltIconOn_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	shieldBigUltIconOn_->getTransform().setPosition(glm::vec3(-6.55f, -3.375f, 1.0f));
	shieldBigUltIconOn_->drawLayer = 10;
	objectsList.push_back(shieldBigUltIconOn_);
	shieldBigUltIconOn = shieldBigUltIconOn_;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Shield Skills Icon
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* dashIcon_ = new TexturedObject("Shield Small Ultimate Icon Off");
	dashIcon_->setTexture("../Resource/Texture/UI/Dash/Dash_On.png");
	dashIcon_->getTransform().setScale(glm::vec3(0.37f * 2.25f, 0.34f * 2.25f, 1.0f));
	dashIcon_->getTransform().setPosition(glm::vec3(7.4f, -3.6f, 1.0f));
	dashIcon_->drawLayer = 10;
	objectsList.push_back(dashIcon_);
	dashIcon = dashIcon_;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Shield Skills Icon
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* tutorialOverlay_ = new TexturedObject("tutorialOverlay");
	tutorialOverlay_->setTexture("../Resource/Texture/UI/TutorialOverlay/TutorialOverlay-Ctrl.png");
	tutorialOverlay_->getTransform().setScale(glm::vec3(2.838f * 2.0f, 1.307f * 2.0f, 1.0f));
	tutorialOverlay_->getTransform().setPosition(glm::vec3(-5.0f, 3.1f, 1.0f));
	tutorialOverlay_->drawLayer = 10;
	objectsList.push_back(tutorialOverlay_);
	tutorialOverlay = tutorialOverlay_;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Shield Skills Icon
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* bow1 = new TexturedObject("tutorialOverlay");
	bow1->setTexture("../Resource/Texture/UI/TutorialOverlay/TutorialOverlay-Ctrl.png");
	bow1->getTransform().setScale(glm::vec3(0.18f * 2.0f, 0.18f * 2.0f, 1.0f));
	bow1->getTransform().setPosition(glm::vec3(bowStatue->getTransform().getPosition().x, bowStatue->getTransform().getPosition().y + 1.0f, 1.0f));
	bow1->drawLayer = 10;
	objectsList.push_back(bow1);
	bowStatue2 = bow1;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Shield Skills Icon
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* sword1 = new TexturedObject("tutorialOverlay");
	sword1->setTexture("../Resource/Texture/UI/TutorialOverlay/TutorialOverlay-Ctrl.png");
	sword1->getTransform().setScale(glm::vec3(0.18f * 2.0f, 0.18f * 2.0f, 1.0f));
	sword1->getTransform().setPosition(glm::vec3(swordStatue->getTransform().getPosition().x, swordStatue->getTransform().getPosition().y + 1.0f, 1.0f));
	sword1->drawLayer = 10;
	objectsList.push_back(sword1);
	swordStatue2 = sword1;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Shield Skills Icon
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* shield1 = new TexturedObject("tutorialOverlay");
	shield1->setTexture("../Resource/Texture/UI/TutorialOverlay/TutorialOverlay-Ctrl.png");
	shield1->getTransform().setScale(glm::vec3(0.18f * 2.0f, 0.18f * 2.0f, 1.0f));
	shield1->getTransform().setPosition(glm::vec3(shieldStatue->getTransform().getPosition().x, shieldStatue->getTransform().getPosition().y + 1.5f, 1.0f));
	shield1->drawLayer = 10;
	objectsList.push_back(shield1);
	shieldStatue2 = shield1;
}

void LevelLimbo1::updateSkillsIcon() {

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

		if (player->getCanDash()) {
			dashIcon->setTexture("../Resource/Texture/UI/Dash/Dash_On.png");
		}
		else {
			dashIcon->setTexture("../Resource/Texture/UI/Dash/Dash_Off.png");
		}

		if (GameEngine::getInstance()->getInputHandler()->getLastInput() == InputDevice::CONTROLLER) {
			tutorialOverlay->setTexture("../Resource/Texture/UI/TutorialOverlay/TutorialOverlay-Ctrl.png");
		}
		else {
			tutorialOverlay->setTexture("../Resource/Texture/UI/TutorialOverlay/TutorialOverlay-MKB.png");
		}
	}
}

void LevelLimbo1::playerUltimateInput() {
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

void LevelLimbo1::updateUIBar() {
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

void LevelLimbo1::stateMachineUpdate(float dt) {
	if (player->getStateMachine()) {
		player->getStateMachine()->update(player, dt);
		//cout << player->getTransform().getPosition().x << endl;
		if (player->getTransform().getPosition().x > 9.0f) {
			player->getTransform().setPosition(glm::vec3(7.5f, player->getTransform().getPosition().y, 0.0f));
			nextLevel();
		}
		if (player->getTransform().getPosition().x < -7.5f) {
			player->getTransform().setPosition(glm::vec3(-7.5f, player->getTransform().getPosition().y, 0.0f));
		}

		if (player->getSword()) {
			DrawableObject* obj = player->getSword()->getChainAttackObject(5);

			PlayerAttackCollider* pAttack = dynamic_cast<PlayerAttackCollider*>(obj);
			if (pAttack) {
				pAttack->getAnimationComponent()->updateCurrentState(dt);
			}
		}
	}

	if (vergil->getStateMachine()) {
		if (vergil->getPlayerInside()) {
			vergil->getStateMachine()->changeState(VergilHightlightState::getInstance(), vergil);
		}
		else {
			vergil->getStateMachine()->changeState(VergilIdleState::getInstance(), vergil);
		}
		vergil->getStateMachine()->update(vergil, dt);

		if (vergil->getAnimationComponent()) {
			vergil->getAnimationComponent()->updateCurrentState(dt);
		}
	}
}

bool LevelLimbo1::isPausing(float dt) {
	if (currentMenuState == MenuState::MAIN) { // isnt Pausing


		return false;
	}

	return true;
}

void LevelLimbo1::changeMenuState(MenuState targetState) {
	if (targetState == currentMenuState || transitioning) return;

	selectedIndex = -1;

	nextMenuState = targetState;
	transitionTime = 0.0f;
	transitioning = true;
}

MenuState LevelLimbo1::getMenuState() const {
	return currentMenuState;
}

void LevelLimbo1::mouseUIHandling(int type, float x, float y) {
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
		if (type == 1) {
			changeMenuState(MenuState::MAIN);
		}
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
	case MenuState::QUITCONFIRM:
		currentList = &quitConfirmButtons;
		if (type == 1) {
			changeMenuState(MenuState::PAUSE);
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
				else {
					SoundManager::GetInstance()->PlaySFX("Misc-ButtonClick");
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

void LevelLimbo1::keyboardUIHandling(char key) {
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
	case MenuState::QUITCONFIRM:
		currentList = &quitConfirmButtons;
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
			SoundManager::GetInstance()->PlaySFX("Misc-ButtonClick");
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

glm::vec2 LevelLimbo1::convertMouseToGameSpace(int mouseX, int mouseY) {
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

void LevelLimbo1::changeSelection(int direction) {

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
	case MenuState::QUITCONFIRM:
		currentList = &quitConfirmButtons;
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

void LevelLimbo1::buttonsFree() {

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

	for (UIButton*& button : quitConfirmButtons) {
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
	quitConfirmButtons.clear();
}

void LevelLimbo1::UIUpdate() {
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
	case MenuState::QUITCONFIRM:
		currentList = &quitConfirmButtons;
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

void LevelLimbo1::createPauseUI() {
	float audioSettingsOffsetY = 0.2f;

	TexturedObject* blackDim = new TexturedObject("blackDim");
	blackDim->setTexture("../Resource/Texture/blackFade.png");
	blackDim->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	blackDim->setMaximumAlpha(0.875f);
	blackDim->drawLayer = 999;
	blackDim->setMenuState(MenuState::PAUSE);
	blackDim->addMenuStateToVec(MenuState::OPTIONS);
	blackDim->addMenuStateToVec(MenuState::AUDIO);
	blackDim->addMenuStateToVec(MenuState::CREDITS);
	blackDim->addMenuStateToVec(MenuState::CONTROLLER);
	blackDim->addMenuStateToVec(MenuState::KEYBOARD);
	blackDim->addMenuStateToVec(MenuState::QUITCONFIRM);
	objectsList.push_back(blackDim);

	TexturedObject* pauseBackground = new TexturedObject("pauseBackground");
	pauseBackground->setTexture("../Resource/Texture/UI/pauseMenu.png");
	pauseBackground->getTransform().setScale(glm::vec3(2.82f * 2.5f, 2.77f * 2.5f, 1.0f));
	pauseBackground->setMenuState(MenuState::PAUSE);
	pauseBackground->addMenuStateToVec(MenuState::QUITCONFIRM);
	pauseBackground->drawLayer = 999;
	objectsList.push_back(pauseBackground);

	TexturedObject* background2 = new TexturedObject("Background2");
	background2->setTexture("../Resource/Texture/newMainMenuBGOnly.png");
	background2->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background2->setMenuState(MenuState::OPTIONS);
	background2->addMenuStateToVec(MenuState::AUDIO);
	background2->addMenuStateToVec(MenuState::CREDITS);
	background2->addMenuStateToVec(MenuState::CONTROLLER);
	background2->addMenuStateToVec(MenuState::KEYBOARD);
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

	TexturedObject* overlayMKB = new TexturedObject();
	overlayMKB->setTexture("../Resource/Texture/KB_Bundle.png");
	overlayMKB->getTransform().setPosition(glm::vec3(-4.8f, -4.0f, 1.0f));
	overlayMKB->getTransform().setScale(glm::vec3(2.382f * 2.2f, 0.277f * 2.2f, 1.0f));
	overlayMKB->setMenuState(MenuState::PAUSE);
	overlayMKB->addMenuStateToVec(MenuState::OPTIONS);
	overlayMKB->addMenuStateToVec(MenuState::AUDIO);
	overlayMKB->addMenuStateToVec(MenuState::CREDITS);
	overlayMKB->addMenuStateToVec(MenuState::CONTROLLER);
	overlayMKB->addMenuStateToVec(MenuState::KEYBOARD);
	overlayMKB->addMenuStateToVec(MenuState::QUITCONFIRM);
	overlayMKB->drawLayer = 999;
	objectsList.push_back(overlayMKB);
	kbOverlay = overlayMKB;

	TexturedObject* overlayController = new TexturedObject();
	overlayController->setTexture("../Resource/Texture/Controller_Bundle.png");
	overlayController->getTransform().setPosition(glm::vec3(-4.8f, -4.0f, 1.0f));
	overlayController->getTransform().setScale(glm::vec3(2.382f * 2.2f, 0.277f * 2.2f, 1.0f));
	overlayController->setMenuState(MenuState::PAUSE);
	overlayController->addMenuStateToVec(MenuState::OPTIONS);
	overlayController->addMenuStateToVec(MenuState::AUDIO);
	overlayController->addMenuStateToVec(MenuState::CREDITS);
	overlayController->addMenuStateToVec(MenuState::CONTROLLER);
	overlayController->addMenuStateToVec(MenuState::KEYBOARD);
	overlayController->addMenuStateToVec(MenuState::QUITCONFIRM);
	overlayController->drawLayer = 999;
	objectsList.push_back(overlayController);
	controllerOverlay = overlayController;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Lines
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SimpleObject* line1 = new SimpleObject();
	line1->setColor(1.0f, 1.0f, 1.0f);
	line1->getTransform().setScale(glm::vec3(14.0f, 0.01f, 0.0f));
	line1->getTransform().setPosition(glm::vec3(0.0f, 3.3f, 0.0f));
	line1->setMenuState(MenuState::OPTIONS);
	line1->addMenuStateToVec(MenuState::AUDIO);
	line1->addMenuStateToVec(MenuState::CREDITS);
	line1->drawLayer = 999;
	objectsList.push_back(line1);

	SimpleObject* line2 = new SimpleObject();
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
	//										Texts
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* staticPauseText = new UIText("Static Pause Text");
	SDL_Color staticPauseTextColor = { 255,255,255,255 };
	staticPauseText->loadText("PAUSED", staticPauseTextColor, 100, true);
	staticPauseText->setText("PAUSED");
	staticPauseText->setAlpha(1.0f);
	staticPauseText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	staticPauseText->getTransform().setPosition(glm::vec3(0.425f, 1.5f, 0.0f));
	staticPauseText->getTransform().setScale(glm::vec3(3.0f, 1.5f, 0.0f));
	staticPauseText->addColliderComponent();
	staticPauseText->setMenuState(MenuState::PAUSE);
	staticPauseText->drawLayer = 999;
	/*staticPauseText->setDrawCollider(true);
	staticPauseText->setCanDrawColliderNew(true);*/
	objectsList.push_back(staticPauseText);

	UIText* staticSettingsText = new UIText("Static Settings Text");
	SDL_Color staticSettingsTextColor = { 255,255,255,255 };
	staticSettingsText->loadText("SETTINGS", staticSettingsTextColor, 100, true);
	staticSettingsText->setText("SETTINGS");
	staticSettingsText->setAlpha(1.0f);
	staticSettingsText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	staticSettingsText->getTransform().setPosition(glm::vec3(0.05f, 3.6f, 0.0f));
	staticSettingsText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	staticSettingsText->addColliderComponent();
	staticSettingsText->setMenuState(MenuState::OPTIONS);
	staticSettingsText->drawLayer = 999;
	/*staticSettingsText->setDrawCollider(true);
	staticSettingsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(staticSettingsText);

	UIText* staticAudioText = new UIText("Static Audio Text");
	SDL_Color staticAudioTextColor = { 255,255,255,255 };
	staticAudioText->loadText("AUDIO", staticAudioTextColor, 100, true);
	staticAudioText->setText("AUDIO");
	staticAudioText->setAlpha(1.0f);
	staticAudioText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	staticAudioText->getTransform().setPosition(glm::vec3(0.29f, 3.6f, 0.0f));
	staticAudioText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	staticAudioText->addColliderComponent();
	staticAudioText->setMenuState(MenuState::AUDIO);
	staticAudioText->drawLayer = 999;
	/*staticAudioText->setDrawCollider(true);
	staticAudioText->setCanDrawColliderNew(true);*/
	objectsList.push_back(staticAudioText);

	UIText* staticQuitText = new UIText("Static Quit Text");
	SDL_Color staticQuitTextColor = { 255,255,255,255 };
	staticQuitText->loadText("QUIT TO MENU?", staticQuitTextColor, 100, true);
	staticQuitText->setText("QUIT TO MENU?");
	staticQuitText->setAlpha(1.0f);
	staticQuitText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	staticQuitText->getTransform().setPosition(glm::vec3(0.45f, 1.5f, 0.0f));
	staticQuitText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	staticQuitText->addColliderComponent();
	staticQuitText->setMenuState(MenuState::QUITCONFIRM);
	staticQuitText->drawLayer = 999;
	/*staticQuitText->setDrawCollider(true);
	staticQuitText->setCanDrawColliderNew(true);*/
	objectsList.push_back(staticQuitText);

	UIText* staticSaveText = new UIText("Static Save Text");
	SDL_Color staticSaveTextColor = { 255,255,255,255 };
	staticSaveText->loadText("PROGRESS WILL BE SAVED.", staticSaveTextColor, 100, true);
	staticSaveText->setText("PROGRESS WILL BE SAVED.");
	staticSaveText->setAlpha(1.0f);
	staticSaveText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	staticSaveText->getTransform().setPosition(glm::vec3(1.1f, -2.0f, 0.0f));
	staticSaveText->getTransform().setScale(glm::vec3(6.0f, 0.75f, 0.0f));
	staticSaveText->addColliderComponent();
	staticSaveText->setMenuState(MenuState::QUITCONFIRM);
	staticSaveText->drawLayer = 999;
	/*staticSaveText->setDrawCollider(true);
	staticSaveText->setCanDrawColliderNew(true);*/
	objectsList.push_back(staticSaveText);

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
	continueText->getTransform().setPosition(glm::vec3(0.25f, 0.6f, 0.0f));
	continueText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	continueText->addColliderComponent();
	continueText->setMenuState(MenuState::PAUSE);
	continueText->drawLayer = 999;
	/*continueText->setDrawCollider(true);
	continueText->setCanDrawColliderNew(true);*/
	objectsList.push_back(continueText);

	UIButton* continueButton = new UIButton("Continue Button");
	//continueButton->setTexture("../Resource/Texture/UI/UIButton.png");
	continueButton->getTransform().setPosition(glm::vec3(0.0f, 0.85f, 0.0f));
	continueButton->getTransform().setScale(glm::vec3(1.6f, 0.35f, 0.0f));
	continueButton->addColliderComponent();
	continueButton->setDrawCollider(true);
	continueButton->setCanDrawColliderNew(false);
	continueButton->setDraw(false);
	continueButton->setLabel(continueText); // Link continueText
	continueButton->setMenuState(MenuState::PAUSE);
	continueButton->setFunction([this]() { changeMenuState(MenuState::MAIN);});
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
	settingsText->getTransform().setPosition(glm::vec3(0.41f, -0.55f, 0.0f));
	settingsText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	settingsText->addColliderComponent();
	settingsText->setMenuState(MenuState::PAUSE);
	settingsText->drawLayer = 999;
	/*settingsText->setDrawCollider(true);
	settingsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(settingsText);

	UIButton* settingsButton = new UIButton("Settings Button");
	//settingsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	settingsButton->getTransform().setPosition(glm::vec3(0.0f, -0.3f, 0.0f));
	settingsButton->getTransform().setScale(glm::vec3(1.2f, 0.35f, 0.0f));
	settingsButton->addColliderComponent();
	settingsButton->setDrawCollider(true);
	settingsButton->setCanDrawColliderNew(false);
	settingsButton->setDraw(false);
	settingsButton->setLabel(settingsText); // Link playText
	settingsButton->setMenuState(MenuState::PAUSE);
	settingsButton->drawLayer = 999;
	settingsButton->setFunction([this]() { changeMenuState(MenuState::OPTIONS);});
	objectsList.push_back(settingsButton);
	buttonsList.push_back(settingsButton);

	pauseButtons.push_back(settingsButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//										Quit Button
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* quitText = new UIText("Quit Text");
	SDL_Color quitTextColor = { 255,255,255,255 };
	quitText->loadText("Quit To Menu", quitTextColor, 100);
	quitText->setText("Quit To Menu");
	quitText->setAlpha(1.0f);
	quitText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	quitText->getTransform().setPosition(glm::vec3(0.9f, -1.7f, 0.0f));
	quitText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	quitText->addColliderComponent();
	quitText->setMenuState(MenuState::PAUSE);
	quitText->drawLayer = 999;
	/*quitText->setDrawCollider(true);
	quitText->setCanDrawColliderNew(true);*/
	objectsList.push_back(quitText);

	UIButton* quitButton = new UIButton("Quit Button");
	//creditsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	quitButton->getTransform().setPosition(glm::vec3(0.0f, -1.45f, 0.0f));
	quitButton->getTransform().setScale(glm::vec3(2.2f, 0.35f, 0.0f));
	quitButton->addColliderComponent();
	quitButton->setDrawCollider(true);
	quitButton->setCanDrawColliderNew(false);
	quitButton->setDraw(false);
	quitButton->setLabel(quitText); // Link playText
	quitButton->setMenuState(MenuState::PAUSE);
	quitButton->setFunction([this]() { changeMenuState(MenuState::QUITCONFIRM);});
	quitButton->drawLayer = 999;
	objectsList.push_back(quitButton);
	buttonsList.push_back(quitButton);

	pauseButtons.push_back(quitButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Audio Button (Settings)
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* audioText = new UIText("Audio Text");
	SDL_Color audioTextColor = { 255,255,255,255 };
	audioText->loadText("Audio", audioTextColor, 100);
	audioText->setText("Audio");
	audioText->setAlpha(1.0f);
	audioText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	audioText->getTransform().setPosition(glm::vec3(-5.5f, 2.15f, 0.0f));
	audioText->getTransform().setScale(glm::vec3(1.0f, 1.0f, 0.0f));
	audioText->addColliderComponent();
	audioText->setMenuState(MenuState::OPTIONS);
	audioText->drawLayer = 999;
	/*audioText->setDrawCollider(true);
	audioText->setCanDrawColliderNew(true);*/
	objectsList.push_back(audioText);

	UIButton* audioButton = new UIButton("Audio Button");
	//audioButton->setTexture("../Resource/Texture/UI/UIButton.png");
	audioButton->getTransform().setPosition(glm::vec3(-5.5f, 2.4f, 0.0f));
	audioButton->getTransform().setScale(glm::vec3(1.0f, 0.35f, 0.0f));
	audioButton->addColliderComponent();
	audioButton->setDrawCollider(true);
	audioButton->setCanDrawColliderNew(false);
	audioButton->setDraw(false);
	audioButton->setLabel(audioText); // Link playText
	audioButton->setMenuState(MenuState::OPTIONS);
	audioButton->setFunction([this]() { changeMenuState(MenuState::AUDIO);});
	audioButton->drawLayer = 999;
	objectsList.push_back(audioButton);
	buttonsList.push_back(audioButton);

	optionsButtons.push_back(audioButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Controller Button (Settings)
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* controllerText = new UIText("Controller Text");
	SDL_Color controllerTextColor = { 255,255,255,255 };
	controllerText->loadText("Controller", controllerTextColor, 100);
	controllerText->setText("Controller");
	controllerText->setAlpha(1.0f);
	controllerText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	controllerText->getTransform().setPosition(glm::vec3(-5.0f, 1.5f, 0.0f));
	controllerText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	controllerText->addColliderComponent();
	controllerText->setMenuState(MenuState::OPTIONS);
	controllerText->drawLayer = 999;
	/*controllerText->setDrawCollider(true);
	controllerText->setCanDrawColliderNew(true);*/
	objectsList.push_back(controllerText);

	UIButton* controllerButton = new UIButton("Controller Button");
	//controllerButton->setTexture("../Resource/Texture/UI/UIButton.png");
	controllerButton->getTransform().setPosition(glm::vec3(-5.2f, 1.75f, 0.0f));
	controllerButton->getTransform().setScale(glm::vec3(1.6f, 0.35f, 0.0f));
	controllerButton->addColliderComponent();
	controllerButton->setDrawCollider(true);
	controllerButton->setCanDrawColliderNew(false);
	controllerButton->setDraw(false);
	controllerButton->setLabel(controllerText); // Link playText
	controllerButton->setMenuState(MenuState::OPTIONS);
	controllerButton->setFunction([this]() { changeMenuState(MenuState::CONTROLLER);});
	controllerButton->drawLayer = 999;
	objectsList.push_back(controllerButton);
	buttonsList.push_back(controllerButton);

	optionsButtons.push_back(controllerButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Keyboard Button (Settings)
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* keyboardText = new UIText("Keyboard Text");
	SDL_Color keyboardTextColor = { 255,255,255,255 };
	keyboardText->loadText("Keyboard", keyboardTextColor, 100);
	keyboardText->setText("Keyboard");
	keyboardText->setAlpha(1.0f);
	keyboardText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	keyboardText->getTransform().setPosition(glm::vec3(-5.0f, 0.85f, 0.0f));
	keyboardText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	keyboardText->addColliderComponent();
	keyboardText->setMenuState(MenuState::OPTIONS);
	keyboardText->drawLayer = 999;
	/*keyboardText->setDrawCollider(true);
	keyboardText->setCanDrawColliderNew(true);*/
	objectsList.push_back(keyboardText);

	UIButton* keyboardButton = new UIButton("Keyboard Button");
	//keyboardButton->setTexture("../Resource/Texture/UI/UIButton.png");
	keyboardButton->getTransform().setPosition(glm::vec3(-5.25f, 1.1f, 0.0f));
	keyboardButton->getTransform().setScale(glm::vec3(1.5f, 0.35f, 0.0f));
	keyboardButton->addColliderComponent();
	keyboardButton->setDrawCollider(true);
	keyboardButton->setCanDrawColliderNew(false);
	keyboardButton->setDraw(false);
	keyboardButton->setLabel(keyboardText); // Link playText
	keyboardButton->setMenuState(MenuState::OPTIONS);
	keyboardButton->setFunction([this]() { changeMenuState(MenuState::KEYBOARD);});
	keyboardButton->drawLayer = 999;
	objectsList.push_back(keyboardButton);
	buttonsList.push_back(keyboardButton);

	optionsButtons.push_back(keyboardButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Yes, No (Quit Confirm)
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float quitConfirmOffset = 0.3f;


	UIText* yesText = new UIText("Yes Text");
	SDL_Color yesTextColor = { 255,255,255,255 };
	yesText->loadText("YES", yesTextColor, 100);
	yesText->setText("YES");
	yesText->setAlpha(1.0f);
	yesText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	yesText->getTransform().setPosition(glm::vec3(0.18f, 0.4f - quitConfirmOffset, 0.0f));
	yesText->getTransform().setScale(glm::vec3(1.0f, 1.0f, 0.0f));
	yesText->addColliderComponent();
	yesText->setMenuState(MenuState::QUITCONFIRM);
	yesText->drawLayer = 999;
	/*yesText->setDrawCollider(true);
	yesText->setCanDrawColliderNew(true);*/
	objectsList.push_back(yesText);

	UIButton* yesButton = new UIButton("Yes Button");
	//yesButton->setTexture("../Resource/Texture/UI/UIButton.png");
	yesButton->getTransform().setPosition(glm::vec3(0.0f, 0.65f - quitConfirmOffset, 0.0f));
	yesButton->getTransform().setScale(glm::vec3(0.7f, 0.35f, 0.0f));
	yesButton->addColliderComponent();
	yesButton->setDrawCollider(true);
	yesButton->setCanDrawColliderNew(false);
	yesButton->setDraw(false);
	yesButton->setLabel(yesText); // Link playText
	yesButton->setMenuState(MenuState::QUITCONFIRM);
	yesButton->setFunction([this]() { toLoadingScreen();});
	yesButton->drawLayer = 999;
	objectsList.push_back(yesButton);
	buttonsList.push_back(yesButton);

	quitConfirmButtons.push_back(yesButton);

	///////////////////////////////////////////////////

	UIText* noText = new UIText("No Text");
	SDL_Color noTextColor = { 255,255,255,255 };
	noText->loadText("NO", yesTextColor, 100);
	noText->setText("NO");
	noText->setAlpha(1.0f);
	noText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	noText->getTransform().setPosition(glm::vec3(0.2f, -0.25f - quitConfirmOffset, 0.0f));
	noText->getTransform().setScale(glm::vec3(1.0f, 1.0f, 0.0f));
	noText->addColliderComponent();
	noText->setMenuState(MenuState::QUITCONFIRM);
	noText->drawLayer = 999;
	/*noText->setDrawCollider(true);
	noText->setCanDrawColliderNew(true);*/
	objectsList.push_back(noText);

	UIButton* noButton = new UIButton("No Button");
	//noButton->setTexture("../Resource/Texture/UI/UIButton.png");
	noButton->getTransform().setPosition(glm::vec3(0.0f, 0.0f - quitConfirmOffset, 0.0f));
	noButton->getTransform().setScale(glm::vec3(0.6f, 0.35f, 0.0f));
	noButton->addColliderComponent();
	noButton->setDrawCollider(true);
	noButton->setCanDrawColliderNew(false);
	noButton->setDraw(false);
	noButton->setLabel(noText); // Link playText
	noButton->setMenuState(MenuState::QUITCONFIRM);
	noButton->setFunction([this]() { changeMenuState(MenuState::PAUSE);});
	noButton->drawLayer = 999;
	objectsList.push_back(noButton);
	buttonsList.push_back(noButton);

	quitConfirmButtons.push_back(noButton);
}

void LevelLimbo1::controllerUIHandling(SDL_GameControllerButton button) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();

	bool input = false;

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
	case MenuState::QUITCONFIRM:
		currentList = &quitConfirmButtons;
		break;
	default:
		return;
	}

	switch (button) {
	case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
		if (isHolding == false) {
			if (focusedButton) {
				SliderObject* slider = focusedButton->getSlider();
				if (slider) {
					slider->setValue(slider->getValue() - 0.025f);
				}
			}
			isHolding = true;
			input = true;
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
			input = true;
		}


		break;
	case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:

		if (isHolding == false) {
			if (focusedButton) {
				SliderObject* slider = focusedButton->getSlider();
				if (slider) {
					slider->setValue(slider->getValue() + 0.025f);
				}
			}
			isHolding = true;
			input = true;
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
			input = true;
		}


		break;
	case SDL_CONTROLLER_BUTTON_DPAD_UP:
		changeSelection(-1);
		input = true;
		break;
	case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
		changeSelection(1);
		input = true;
		break;
	case SDL_CONTROLLER_BUTTON_B:
		if (currentMenuState == OPTIONS) {
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
			changeMenuState(MenuState::MAIN);
		}
		else if (currentMenuState == PAUSE) {
			changeMenuState(MenuState::MAIN);
		}
		input = true;
		break;
	case SDL_CONTROLLER_BUTTON_A:
		/*if (selectedButton && selectedButton->getMouseOver()) {
			selectedButton->OnClick();
		}*/

		if (focusedButton && focusedButton->getMouseOver()) {
			focusedButton->OnClick();
			SoundManager::GetInstance()->PlaySFX("Misc-ButtonClick");
			input = true;
		}

		break;
	}


	if (!input) {
		if (isHolding == true) {
			isHolding = false;
		}
		if (holdButtonTimer > 0) {
			holdButtonTimer = 0;
		}
	}
}