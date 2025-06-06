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

	posingBeforeQTE = false;
	timerbeforeQTE = 0.08f * 8;

	needToPose = false;
	recoveryPosed = false;
	timerAfterQTE = 0.08f * 10;

	/*randomQTETarget();
	startQTE(QTETarget);*/

	randomQTESequence();

	

	bufferTimerFailure = 0.25f;
	bufferTimerSuccess = 0.25f;
	ziz->setTexture("../Resource/Texture/FinalZiz/QTE/qtestart1.png", 1, 8, 0);

	ziz->getAnimationComponent()->setState("qtestart1");
	ziz->facePlayer();
	
}

void ZizQTEState::update(Boss* boss, float dt) {
	
	if (posingBeforeQTE == false) {
		if (timerbeforeQTE > 0) {
			timerbeforeQTE -= dt;
			if (timerbeforeQTE <= 0) {
				startQTE(QTETarget1);
				qteButtonUI = ziz->createQTEButtonUI();
				ziz->getLevel()->addObject(qteButtonUI);
				ziz->setTexture("../Resource/Texture/FinalZiz/QTE/qtestart2.png", 1, 16, 0);
				ziz->getAnimationComponent()->setState("qtestart2");
				posingBeforeQTE = true;
			}
		}
	}
	else {
		if (failedAny == false) {
			switch (currentSeq) {
			case 0:
				if (timer1 > 0) {
					timer1 -= dt;
					if (ziz->getQTEInputReceieved() == true) {
						if (ziz->getQTECorrect() == true) {
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
						else if (ziz->getQTECorrect() == false) {
							ziz->startShake(0.1f, 0.005f);
							//cout << "wrong 1st" << endl;
							qteButtonUI->changeTextureFailure(QTETarget1);
							ziz->endQTEMode();
							failedAny = true;
						}

					}
					if (timer1 <= 0) {
						ziz->startShake(0.1f, 0.005f);
						//cout << "time ran out 1st" << endl;
						qteButtonUI->changeTextureFailure(QTETarget1);
						ziz->endQTEMode();
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
						else if (ziz->getQTECorrect() == false) {
							ziz->startShake(0.1f, 0.005f);
							//cout << "wrong 2nd" << endl;
							qteButtonUI->changeTextureFailure(QTETarget2);
							ziz->endQTEMode();
							failedAny = true;
						}

					}
					if (timer2 <= 0) {
						ziz->startShake(0.1f, 0.005f);
						//cout << "time ran out 2nd" << endl;
						qteButtonUI->changeTextureFailure(QTETarget2);
						ziz->endQTEMode();
						
						failedAny = true;
					}
				}
				break;
			case 2:
				if (timer3 > 0) {
					timer3 -= dt;
					if (ziz->getQTEInputReceieved() == true) {
						if (ziz->getQTECorrect() == true) {
							//cout << "correct 3rd" << endl;
							qteButtonUI->changeTextureSuccess(QTETarget3);

							currentSeq++;
						}
						else if (ziz->getQTECorrect() == false) {
							ziz->startShake(0.1f, 0.005f);
							//cout << "wrong 3rd" << endl;
							qteButtonUI->changeTextureFailure(QTETarget3);
							ziz->endQTEMode();
							failedAny = true;
						}

					}
					if (timer2 <= 0) {
						ziz->startShake(0.1f, 0.005f);
						//cout << "time ran out 3rd" << endl;
						qteButtonUI->changeTextureFailure(QTETarget3);
						ziz->endQTEMode();
						failedAny = true;
					}
				}
				break;

			case 3:
				if (needToPose == false) {
					ziz->setTexture("../Resource/Texture/FinalZiz/QTE/qtestart3.png", 1, 10, 0);
					ziz->getAnimationComponent()->setState("qterecovery");
					ziz->endQTEMode();
					qteButtonUI->expire();

					needToPose = true;
				}


				if (ziz->getTransform().getPosition().y < 8.0f) {
					if (recoveryPosed == false) {
						if (timerAfterQTE > 0) {
							//cout << "timerafterqte" << endl;
							timerAfterQTE -= dt;
							if (timerAfterQTE <= 0) {
								recoveryPosed = true;
							}
						}
					}
					else {
						ziz->getStateMachine()->changeState(ZizSwoopState::getInstance(), ziz);
					}
				}
				else {
					ziz->getStateMachine()->changeState(ZizSwoopState::getInstance(), ziz);
				}
			default:
				break;
			}
		}
	}


	if (failedAny == true) {
		if (ziz->getTransform().getPosition().y < 8.0f) {
			if (recoveryPosed == false) {
				if (timerAfterQTE > 0) {
					timerAfterQTE -= dt;
					if (timerAfterQTE <= 0) {
						recoveryPosed = true;
					}
				}
			}
			else {
				ziz->getStateMachine()->changeState(ZizImpaleState::getInstance(), ziz);
			}
		}
		else {
			ziz->getStateMachine()->changeState(ZizImpaleState::getInstance(), ziz);
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