#include "ZizQTEState.h"
#include "LevelBossTest.h"
#include "QTEButtonUI.h"
#include <cstdlib>

ZizQTEState* ZizQTEState::instance = nullptr;

ZizQTEState* ZizQTEState::getInstance() {
	if (!instance) {
		instance = new ZizQTEState;
	}

	return instance;
}

void ZizQTEState::enter(Boss* boss) {

	
	ziz = Ziz::getInstance();
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
	qteButtonUI = ziz->createQTEButtonUI();
	ziz->getLevel()->addObject(qteButtonUI);

	bufferTimerFailure = 0.25f;
	bufferTimerSuccess = 0.25f;
	
}

void ZizQTEState::update(Boss* boss, float dt) {
	//if (timer > 0) {
	//	timer -= dt;
	//	if (timer <= 0) {//out of time
	//		ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
	//	}

	//	if (ziz->getQTEInputReceieved() == true) {
	//		if (ziz->getQTECorrect() == true) {
	//			cout << "correct state" << endl;
	//		}
	//		else if(ziz->getQTECorrect() == false){
	//			cout << "wrong state" << endl;
	//		}
	//		ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
	//	}
	//}

	if (failedAny == false) {
		switch (currentSeq) {
		case 0:
			if (timer1 > 0) {
				timer1 -= dt;
				if (ziz->getQTEInputReceieved() == true) {
					if (ziz->getQTECorrect() == true) {
						qteButtonUI->changeTextureSuccess(QTETarget1);

						if (bufferTimerSuccess > 0) {
							cout << "buffering success" << endl;
							bufferTimerSuccess -= dt;
							if (bufferTimerSuccess <= 0) {
								qteButtonUI->changeTextureDefault(QTETarget2);
								startQTE(QTETarget2);
								currentSeq++;
								bufferTimerSuccess = 0.25f;
							}
						}
						
					}
					else if (ziz->getQTECorrect() == false) {
						ziz->startShake(0.1f, 0.005f);
						cout << "wrong 1st" << endl;
						qteButtonUI->changeTextureFailure(QTETarget1);
						failedAny = true;
					}
					
				}
				if (timer1 <= 0) {
					ziz->startShake(0.1f, 0.005f);
					cout << "time ran out 1st" << endl;
					qteButtonUI->changeTextureFailure(QTETarget1);
					failedAny = true;
				}
			}
			break;
		case 1:
			if (timer2 > 0) {
				timer2 -= dt;
				if (ziz->getQTEInputReceieved() == true) {
					if (ziz->getQTECorrect() == true) {

						qteButtonUI->changeTextureSuccess(QTETarget2);

						if (bufferTimerSuccess > 0) {
							cout << "buffering success" << endl;
							bufferTimerSuccess -= dt;
							if (bufferTimerSuccess <= 0) {
								qteButtonUI->changeTextureDefault(QTETarget3);
								startQTE(QTETarget3);
								currentSeq++;
								bufferTimerSuccess = 0.25f;
							}
						}

					}
					else if (ziz->getQTECorrect() == false) {
						ziz->startShake(0.1f, 0.005f);
						cout << "wrong 2nd" << endl;
						qteButtonUI->changeTextureFailure(QTETarget2);
						failedAny = true;
					}
					
				}
				if (timer2 <= 0) {
					ziz->startShake(0.1f, 0.005f);
					cout << "time ran out 2nd" << endl;
					qteButtonUI->changeTextureFailure(QTETarget2);
					failedAny = true;
				}
			}
			break;
		case 2:
			if (timer3 > 0) {
				timer3 -= dt;
				if (ziz->getQTEInputReceieved() == true) {
					if (ziz->getQTECorrect() == true) {
						cout << "correct 3rd" << endl;
						qteButtonUI->changeTextureSuccess(QTETarget3);

						if (bufferTimerSuccess > 0) {
							cout << "buffering success" << endl;
							bufferTimerSuccess -= dt;
							if (bufferTimerSuccess <= 0) {
								ziz->getStateMachine()->changeState(ZizSwoopState::getInstance(), ziz);
							}
						}
					}
					else if (ziz->getQTECorrect() == false) {
						ziz->startShake(0.1f, 0.005f);
						cout << "wrong 3rd" << endl;
						qteButtonUI->changeTextureFailure(QTETarget3);
						failedAny = true;
					}
					
				}
				if (timer2 <= 0) {
					ziz->startShake(0.1f, 0.005f);
					cout << "time ran out 3rd" << endl;
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
			cout << "buffering" << endl;
			if (bufferTimerFailure <= 0) {
				
				ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
			}
		}

		
	}
	


}

void ZizQTEState::exit(Boss* boss) {
	qteButtonUI->expire();
	ziz->endQTEMode();
}

void ZizQTEState::randomQTETarget() {
	QTETarget = (rand() % 3);
	
}

void ZizQTEState::randomQTESequence() {
	QTETarget1 = (rand() % 3);
	QTETarget2 = (rand() % 3);
	QTETarget3 = (rand() % 3);
}

void ZizQTEState::startQTE(int target) {
	ziz->startQTEMode(target);
}