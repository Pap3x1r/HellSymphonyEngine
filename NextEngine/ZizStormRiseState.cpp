#include "ZizStormRiseState.h"
#include "ZizGroundSlamState.h"

ZizStormRiseState* ZizStormRiseState::instance = nullptr;

ZizStormRiseState* ZizStormRiseState::getInstance() {
	if (!instance) {
		instance = new ZizStormRiseState;
	}

	return instance;
}

void ZizStormRiseState::enter(Boss* boss) {
    Ziz* ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    

    
    //ziz->setTexture("../Resource/Ziz/StormRise.png");
    DrawableObject* newStormRise = ziz->createStormRise();
    

    ziz->getLevel()->addObject(newStormRise);
    ziz->facePlayer();



    
    startupTimer1 = 0.08f * 8;
    startupTimer2 = 0.08f * 16;
    activeTimer = 0.08f * 2;
    recoveryTimer1 = 0.08f * 15;
    recoveryTimer2 = 0.08f * 6;
    recoveryTimer3 = 0.08f * 10;

    state = 1;

    
    SoundManager::GetInstance()->PlaySFX("Ziz_StormRise");

    ziz->getAnimationComponent()->setAnimOffset(glm::vec3(-0.015f, 0, 0));
    ziz->setTexture("../Resource/Texture/FinalZiz/stormrise/1_Zyzz_StormRise_StartUp_1.png", 1, 8, 0);
    ziz->getAnimationComponent()->setState("stormrisestartup1");
}

void ZizStormRiseState::update(Boss* boss, float dt) {
    Ziz* ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    //cout << "Ziz Stormrise State: " << state << endl;
    switch (state) {
    case 1:
        if (startupTimer1 > 0) {
            startupTimer1 -= dt;
            if (startupTimer1 <= 0) {
                ziz->setTexture("../Resource/Texture/FinalZiz/stormrise/1_Zyzz_StormRise_StartUp_2.png", 1, 16, 0);
                ziz->getAnimationComponent()->setState("stormrisestartup2");
                state++;
            }
        }
        break;
    case 2:
        if (startupTimer2 > 0) {
            startupTimer2 -= dt;
            if (startupTimer2 <= 0) {
                ziz->setTexture("../Resource/Texture/FinalZiz/stormrise/2_Zyzz_StormRise_Active.png", 1, 2, 0);
                ziz->getAnimationComponent()->setState("stormriseactive");
                state++;
            }
        }
        break;
    case 3:
        if (activeTimer > 0) {
            activeTimer -= dt;
            if (activeTimer <= 0) {
                ziz->setTexture("../Resource/Texture/FinalZiz/stormrise/3_Zyzz_StormRise_Recovery_1.png", 1, 15, 0);
                ziz->getAnimationComponent()->setState("stormriserecovery1");
                state++;
            }
        }
        break;
    case 4:
        if (recoveryTimer1 > 0) {
            recoveryTimer1 -= dt;
            if (recoveryTimer1 <= 0) {
                ziz->setTexture("../Resource/Texture/FinalZiz/stormrise/3_Zyzz_StormRise_Recovery_2.png", 1, 6, 0);
                ziz->getAnimationComponent()->setState("stormriserecovery2");
                state++;
            }
        }
        break;
    case 5:
        if (recoveryTimer2 > 0) {
            recoveryTimer2 -= dt;
            if (recoveryTimer2 <= 0) {
                ziz->setTexture("../Resource/Texture/FinalZiz/stormrise/3_Zyzz_StormRise_Recovery_3.png", 1, 10, 0);
                ziz->getAnimationComponent()->setState("stormriserecovery3");
                state++;
            }
        }
        break;
    case 6:
        if (recoveryTimer3 > 0) {
            recoveryTimer3 -= dt;
            if (recoveryTimer3 <= 0) {
                state++;
                if (ziz->getDistanceFromPlayer() < 3.0f) {
                    if ((rand() % 2) == 0) {
                        ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
                    }
                    else {
                        ziz->getStateMachine()->changeState(ZizWingSpanState::getInstance(), ziz);
                    }

                }
                else {
                    if ((rand() % 11) <= 2) {
                        ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
                    }
                    else if ((rand() % 11) <= 5){
                        ziz->getStateMachine()->changeState(ZizSwoopState::getInstance(), ziz);
                    }
                    else {
                        ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
                    }
                }
            }
        }
        break;

    default:
        break;
    }

    
    
    
}

void ZizStormRiseState::exit(Boss* boss) {
    Ziz* ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;
    ziz->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, 0, 0));
    //cout << "Ziz exiting StormRise State." << endl;
}