#include "LevelBossTest.h"
#include "CollisionHandler.h"
#include "Bow.h"
#include "ZizGroundSlamState.h"
#include "GameEngine.h" // Include GameEngine header
#include "GLRenderer.h" // Include GLRenderer header
#include <iostream>
#include <random>
#include <fstream>
using namespace std;




void LevelBossTest::levelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->loadData();
	GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

	SquareBorderMesh* border = new SquareBorderMesh();
	border->loadData();
	GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);

	//cout << "Load Level" << endl;
	/*GameEngine::getInstance()->getRenderer()->loadTextureFromDir("../Resource/Texture/Dante");
	GameEngine::getInstance()->getRenderer()->loadTextureFromDir("../Resource/Texture/Ziz");
	GameEngine::getInstance()->getRenderer()->loadTextureFromDir("../Resource/Texture/FinalZiz");
	GameEngine::getInstance()->getRenderer()->loadTextureFromDir("../Resource/Texture/FinalZiz/VFX");*/
}

void LevelBossTest::levelInit() {

	TexturedObject* background = new TexturedObject("background");
	background->setTexture("../Resource/Texture/Lust_Alpha.png");
	background->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	objectsList.push_back(background);
	

	Player* player_ = GameEngine::getInstance()->loadPlayerData("../Resource/Saves/PlayerData/playerData.txt");
	objectsList.push_back(player_);
	player = player_;
	player->setLevel(this);
	player->getTransform().setPosition(glm::vec3(-5.0,-0.8f,0.0f));
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

	//Overheat
	TexturedObject* overheatBarBackground = new TexturedObject();
	overheatBarBackground->setTexture("../Resource/Texture/UI/Bow/Overheat_Empty_BG.png");
	overheatBarBackground->getTransform().setScale(glm::vec3(1.37f * 2.75f, 0.02f * 4.5f, 1.0f));
	overheatBarBackground->getTransform().setPosition(glm::vec3(-4.1f, -3.55f, 0.0f));
	objectsList.push_back(overheatBarBackground);
	playerOverheatBarBackground = overheatBarBackground;

	SimpleObject* overheatBar = new SimpleObject();
	overheatBar->setColor(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f);
	overheatBar->getTransform().setScale(glm::vec3(3.665f, 0.08f, 0.0f));
	overheatBar->getTransform().setPosition(glm::vec3(-4.1f, -3.55f, 0.0f));
	objectsList.push_back(overheatBar);
	playerOverheatBar = overheatBar;

	TexturedObject* overheatBarFrame = new TexturedObject();
	overheatBarFrame->setTexture("../Resource/Texture/UI/Bow/Overheat_Frame.png");
	overheatBarFrame->getTransform().setScale(glm::vec3(1.37f * 2.75f, 0.02f * 4.5f, 1.0f));
	overheatBarFrame->getTransform().setPosition(glm::vec3(-4.1f, -3.55f, 0.0f));
	objectsList.push_back(overheatBarFrame);
	playerOverheatBarFrame = overheatBarFrame;

	//Health & Ult UI
	//cout << "Init Level" << endl;
	TexturedObject* healthBarBackground = new TexturedObject();
	healthBarBackground->setTexture("../Resource/Texture/UI/Healthbar_BG.png");
	healthBarBackground->getTransform().setScale(glm::vec3(2.42f * 2.5f, 0.5f * 2.5f, 1.0f));
	healthBarBackground->getTransform().setPosition(glm::vec3(-5.0f, -4.0f, 0.0f));
	objectsList.push_back(healthBarBackground);

	SimpleObject* witherHealthBar_ = new SimpleObject();
	witherHealthBar_->setColor(106.0f / 255.0f, 109.0f / 255.0f, 115.0f / 255.0f);
	witherHealthBar_->getTransform().setScale(glm::vec3(5.375f, 0.23f, 0.0f));
	witherHealthBar_->getTransform().setPosition(glm::vec3(-5.05f, -3.95f, 0.0f));
	objectsList.push_back(witherHealthBar_);
	witherHealthBar = witherHealthBar_;

	SimpleObject* healthBar = new SimpleObject();
	healthBar->setColor(1.0f, 0.0f, 0.0f);
	healthBar->getTransform().setScale(glm::vec3(5.375f, 0.23f, 0.0f));
	healthBar->getTransform().setPosition(glm::vec3(-5.05f, -3.95f, 0.0f));
	objectsList.push_back(healthBar);
	playerHealthBar = healthBar;

	SimpleObject* ultimateBar = new SimpleObject();
	ultimateBar->setColor(235.0f / 255.0f, 168.0f / 255.0f, 52.0f / 255.0f);
	ultimateBar->getTransform().setScale(glm::vec3(3.18f, 0.25f, 0.0f));
	ultimateBar->getTransform().setPosition(glm::vec3(-6.165f, -4.225f, 0.0f));
	objectsList.push_back(ultimateBar);
	playerUltimateBar = ultimateBar;

	TexturedObject* healthBarFrame = new TexturedObject();
	healthBarFrame->setTexture("../Resource/Texture/UI/Healthbar_Frame.png");
	healthBarFrame->getTransform().setScale(glm::vec3(2.42f * 2.5f, 0.5f * 2.5f, 1.0f));
	healthBarFrame->getTransform().setPosition(glm::vec3(-5.0f, -4.0f, 0.0f));
	objectsList.push_back(healthBarFrame);

	SimpleObject* bossHealthBar_ = new SimpleObject();
	bossHealthBar_->setColor(0.0f, 1.0f, 0.0f);
	bossHealthBar_->getTransform().setScale(glm::vec3(9.0f, 0.25f, 0.0f));
	bossHealthBar_->getTransform().setPosition(glm::vec3(0.0f, 4.0f, 0.0f));
	objectsList.push_back(bossHealthBar_);
	bossHealthBar = bossHealthBar_;

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

	//GameEngine::getInstance()->freezeGameForSecond(1.6f);
}

void LevelBossTest::levelUpdate() {
	dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	float playerDT = dt * playerTimeScale;
	timeK += dt;

	if (isPausing(dt)) {
		return;
	}


	updateObjects(objectsList);
	updateSkillsIcon();

	//std::cout << "Current cache size: " << GameEngine::getInstance()->getRenderer()->getTextureCache().size() << std::endl;

	ImGui::SetWindowSize(ImVec2(400, 300));
	ImGui::Begin("Debug Panel");

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

	if (ziz) {
		ziz->phaseChangeTracker();
		ziz->updateShake(dt);
		
	}

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
	
	updateUIBar();

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
	//savePlayerData(player, "../Resource/Saves/PlayerData/playerData.txt");

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

	if (currentMenuState != MenuState::MAIN) {
		if (key == 't') {
			currentMenuState = MenuState::MAIN;
		}
		else if (key == 'l') {
			currentMenuState = MenuState::PAUSE;
		}
		return;
	}



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
		if (player->getIsDashing() == true) return;
		if (player->getIsStunned() == true) return;

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
		//player->startShake(0.1f, 0.0025f);
		//ziz->startShake(0.2f, 0.005f);
		//player->increaseUltimateGauge(100.0f);
		//ziz->interruptPhaseChange();
		currentMenuState = MenuState::MAIN;
		break;
		
	case 'l':

		currentMenuState = MenuState::PAUSE;
		/*UltZizOnBG* ultZizOnBG_ = ziz->createBGZiz();
		addObject(ultZizOnBG_);
		ziz->startShake(0.08f * (12*3.75), 0.0025f);*/

		/*DrawableObject* lightning_ = ziz->createLightning();
		addObject(lightning_);*/
		
		/*DrawableObject* newStormRise = ziz->createStormRise();
		addObject(newStormRise);*/

		/*DrawableObject* newGust = ziz->createGust();
		addObject(newGust);*/

		//ziz->startShake(0.2f, 0.005f);
		//ziz->interruptPhaseChange();
		//ziz->createChompTentacle();
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

	if (currentMenuState != MenuState::MAIN) {
		return;
	}

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

		playerUltimateInput();

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

	if (currentMenuState != MenuState::MAIN) {
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

	if (player->getIsGrounded() == false || player->getIsDashing() == true) { //Prevent air attack and attack while dashing
		return;
	}

	if (player->getIsStunned() == true) return;

	if (player->getWeaponType() == Bow_) {
		if (player->getBow()->getIsShooting() == true) {
			return;
		}
		if (type == 0) {
			if (player->getBow()->getIsOverheat() == false) {
				if (player->getBow()->getRapidShotReady()) {
					player->getStateMachine()->changeState(PlayerLightBowAttack::getInstance(), player);
				}
			}
		}
		else if (type == 1) {
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
			if (player->getShield()->getIsBlocking()) {
				return;
			}

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

	if (currentMenuState != MenuState::MAIN) {
		return;
	}

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

void LevelBossTest::createSkillsIcon() {
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

void LevelBossTest::updateSkillsIcon() {

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

void LevelBossTest::playerUltimateInput() {
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

void LevelBossTest::updateUIBar() {
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

	//Boss Health Bar
	static float bossHealthOriginalWidth = bossHealthBar->getTransform().getScale().x;
	static float bossHealthBaseX = bossHealthBar->getTransform().getPosition().x;

	float bossHealthPercentage = ziz->getHealth()->getCurrentHP() / ziz->getHealth()->getMaxHP();
	//cout << ziz->getHealth()->getCurrentHP() << " " << ziz->getHealth()->getMaxHP() << endl;
	bossHealthPercentage = glm::clamp(bossHealthPercentage, 0.0f, 1.0f);

	float bossHealthWidth = bossHealthPercentage * bossHealthOriginalWidth;

	float bossHealthX = bossHealthBaseX - (bossHealthOriginalWidth * 0.5f) + (bossHealthWidth * 0.5f);

	bossHealthBar->getTransform().setScale(glm::vec3(bossHealthWidth, bossHealthBar->getTransform().getScale().y, bossHealthBar->getTransform().getScale().z));
	bossHealthBar->getTransform().setPosition(glm::vec3(bossHealthX, 4.0f, 0.0f));

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

void LevelBossTest::stateMachineUpdate(float dt) {
	if (ziz->getStateMachine()) {
		ziz->getStateMachine()->update(ziz, dt);
	}

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

bool LevelBossTest::isPausing(float dt) {
	if (currentMenuState == MenuState::MAIN) { // isnt Pausing


		return false;
	}

	return true;
}