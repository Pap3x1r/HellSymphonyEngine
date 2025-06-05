#include "LuciferQTEState.h"
#include "LevelLucifer.h"
#include "QTEButtonUI.h"
#include "LuciferSideLaserState.h"
#include <cstdlib>

LuciferQTEState* LuciferQTEState::instance = nullptr;

LuciferQTEState* LuciferQTEState::getInstance() {
	if (!instance) {
		instance = new LuciferQTEState;
	}

	return instance;
}

void LuciferQTEState::enter(Boss* boss) {


	lucifer = Lucifer::getInstance();
	timer = 3.0f;


	timer1 = 3.0f;
	timer2 = 3.0f;
	timer3 = 3.0f;

	failedAny = false;
	currentSeq = 0;

	/*randomQTETarget();
	startQTE(QTETarget);*/

	randomQTESequence();

	startQTE(QTETarget1);
	qteButtonUI = lucifer->createQTEButtonUI();
	lucifer->getLevel()->addObject(qteButtonUI);

	bufferTimerFailure = 0.25f;
	bufferTimerSuccess = 0.25f;

	waitSpear = 0.0f;

}

void LuciferQTEState::update(Boss* boss, float dt) {

	if (failedAny == false) {
		switch (currentSeq) {
		case 0:
			if (timer1 > 0) {
				timer1 -= dt;
				if (lucifer->getQTEInputReceieved() == true) {
					if (lucifer->getQTECorrect() == true) {
						qteButtonUI->changeTextureSuccess(QTETarget1);

						if (bufferTimerSuccess > 0) {
							//cout << "buffering success" << endl;
							bufferTimerSuccess -= dt;
							if (bufferTimerSuccess <= 0) {
								qteButtonUI->changeTextureDefault(QTETarget2);
								startQTE(QTETarget2);
								currentSeq++;
								bufferTimerSuccess = 0.25f;
							}
						}

					}
					else if (lucifer->getQTECorrect() == false) {
						lucifer->startShake(0.1f, 0.005f);
						//cout << "wrong 1st" << endl;
						qteButtonUI->changeTextureFailure(QTETarget1);
						failedAny = true;
					}

				}
				if (timer1 <= 0) {
					lucifer->startShake(0.1f, 0.005f);
					//cout << "time ran out 1st" << endl;
					qteButtonUI->changeTextureFailure(QTETarget1);
					failedAny = true;
				}
			}
			break;
		case 1:
			if (timer2 > 0) {
				timer2 -= dt;
				if (lucifer->getQTEInputReceieved() == true) {
					if (lucifer->getQTECorrect() == true) {

						qteButtonUI->changeTextureSuccess(QTETarget2);

						if (bufferTimerSuccess > 0) {
							//cout << "buffering success" << endl;
							bufferTimerSuccess -= dt;
							if (bufferTimerSuccess <= 0) {
								qteButtonUI->changeTextureDefault(QTETarget3);
								startQTE(QTETarget3);
								currentSeq++;
								bufferTimerSuccess = 0.25f;
							}
						}

					}
					else if (lucifer->getQTECorrect() == false) {
						lucifer->startShake(0.1f, 0.005f);
						//cout << "wrong 2nd" << endl;
						qteButtonUI->changeTextureFailure(QTETarget2);
						failedAny = true;
					}

				}
				if (timer2 <= 0) {
					lucifer->startShake(0.1f, 0.005f);
					//cout << "time ran out 2nd" << endl;
					qteButtonUI->changeTextureFailure(QTETarget2);
					failedAny = true;
				}
			}
			break;
		case 2:
			if (timer3 > 0) {
				timer3 -= dt;
				if (lucifer->getQTEInputReceieved() == true) {
					if (lucifer->getQTECorrect() == true) {
						//cout << "correct 3rd" << endl;
						qteButtonUI->changeTextureSuccess(QTETarget3);

						if (bufferTimerSuccess > 0) {
							//cout << "buffering success" << endl;
							bufferTimerSuccess -= dt;
							if (bufferTimerSuccess <= 0) {
								IceSpear* is = new IceSpear(lucifer->getPlayer(), 0);
								lucifer->getLevel()->addObject(is);
								qteButtonUI->expire();
								lucifer->getStateMachine()->changeState(LuciferFreeHitState::getInstance(), lucifer);

								
							}
						}
					}
					else if (lucifer->getQTECorrect() == false) {
						lucifer->startShake(0.1f, 0.005f);
						//cout << "wrong 3rd" << endl;
						qteButtonUI->changeTextureFailure(QTETarget3);
						failedAny = true;
					}

				}
				if (timer2 <= 0) {
					lucifer->startShake(0.1f, 0.005f);
					//cout << "time ran out 3rd" << endl;
					qteButtonUI->changeTextureFailure(QTETarget3);
					failedAny = true;
				}
			}
			break;
		
		default:
			break;
		}
	}

	if (failedAny == true) {
		if (bufferTimerFailure > 0) {
			bufferTimerFailure -= dt;
			//cout << "buffering" << endl;
			if (bufferTimerFailure <= 0) {

				lucifer->getStateMachine()->changeState(LuciferSideLaserState::getInstance(), lucifer);
			}
		}


	}



}

void LuciferQTEState::exit(Boss* boss) {
	qteButtonUI->expire();
	lucifer->endQTEMode();
}

void LuciferQTEState::randomQTETarget() {
	QTETarget = (rand() % 3);

}

void LuciferQTEState::randomQTESequence() {
	QTETarget1 = (rand() % 3);
	QTETarget2 = (rand() % 3);
	QTETarget3 = (rand() % 3);
}

void LuciferQTEState::startQTE(int target) {
	lucifer->startQTEMode(target);
}