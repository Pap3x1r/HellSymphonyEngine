#include "ZizGustState.h"


ZizGustState* ZizGustState::instance = nullptr;

ZizGustState* ZizGustState::getInstance() {
	if (!instance) {
		instance = new ZizGustState;
	}

	return instance;
}

void ZizGustState::enter(Boss* boss) {
    ziz = dynamic_cast<Ziz*>(boss);

    
    startupTimer = 0.08f * 7;
    activeTimer = 0.08f * 5;
    recoveryTimer = 0.08f * 8;
    ziz->setTexture("../Resource/Texture/FinalZiz/Zyzz_Gust-Sheet.png", 1, 20, 0);
    //ziz->setTexture("../Resource/Texture/Ziz/Ziz_Gust.png", 1, 20, 0);
    ziz->getAnimationComponent()->setState("gust");
    ziz->facePlayer();

    currentState = 0;
    
    //cout << "start up gust" << endl;
    ziz->getAnimationComponent()->setAnimOffset(glm::vec3(-0.015f, 0, 0));
    SoundManager::GetInstance()->PlaySFX("Ziz_ClawSlash");
    
}

void ZizGustState::update(Boss* boss, float dt) {

    switch (currentState) {
    case 0:
        if (startupTimer > 0) {
            startupTimer -= dt;
        }
        else {
            //cout << "active gust" << endl;
            currentState = 1;
            DrawableObject* newGust = ziz->createGust();
            ziz->getLevel()->addObject(newGust);
        }
        break;
    case 1:
        if (activeTimer > 0) {
            activeTimer -= dt;
        }
        else {
            
            //cout << "recovery gust" << endl;
            currentState = 2;
        }
        break;
    case 2:
        if (recoveryTimer > 0) {
            recoveryTimer -= dt;
        }
        else {
            //cout << "change back to idle from gust" << endl;
            currentState = 3;
        }
        break;
    case 3:
        ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
        break;
    default:
        break;
    }

    
}

void ZizGustState::exit(Boss* boss) {
    ziz->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, 0, 0));
}