#include "ZizQTEState.h"
#include "LevelBossTest.h"
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
						cout << "correct 1st" << endl;
						startQTE(QTETarget2);
						currentSeq++;
					}
					else if (ziz->getQTECorrect() == false) {
						cout << "wrong 1st" << endl;
						failedAny = true;
					}
				}
				if (timer1 <= 0) {
					cout << "time ran out 1st" << endl;
					failedAny = true;
				}
			}
			break;
		case 1:
			if (timer2 > 0) {
				timer2 -= dt;
				if (ziz->getQTEInputReceieved() == true) {
					if (ziz->getQTECorrect() == true) {
						cout << "correct 2nd" << endl;
						startQTE(QTETarget3);
						currentSeq++;
					}
					else if (ziz->getQTECorrect() == false) {
						cout << "wrong 2nd" << endl;
						failedAny = true;
					}
				}
				if (timer2 <= 0) {
					cout << "time ran out 2nd" << endl;
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
						ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
						currentSeq++;
					}
					else if (ziz->getQTECorrect() == false) {
						cout << "wrong 3rd" << endl;
						failedAny = true;
					}
				}
				if (timer2 <= 0) {
					cout << "time ran out 3rd" << endl;
					failedAny = true;
				}
			}
			break;
		default:
			break;
		}
	}

	if (failedAny == true) {
		cout << "failed" << endl;
		ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
	}
	


}

void ZizQTEState::exit(Boss* boss) {
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
	switch (target) {
	case 0://w
		ziz->startQTEMode('w');
		break;
	case 1://a
		ziz->startQTEMode('a');
		break;
	case 2://s
		ziz->startQTEMode('s');
		break;
	case 3://d
		ziz->startQTEMode('d');
		break;
	default:
		break;
	}
}