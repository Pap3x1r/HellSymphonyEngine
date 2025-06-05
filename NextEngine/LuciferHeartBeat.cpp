#include "LuciferHeartBeat.h"


LuciferHeartBeat* LuciferHeartBeat::instance = nullptr;

LuciferHeartBeat* LuciferHeartBeat::getInstance() {
	if (!instance) {
		instance = new LuciferHeartBeat();
	}
	return instance;
}

LuciferHeartBeat::LuciferHeartBeat() {


	initAnimation(8, 1);
	getAnimationComponent()->addState("heartbeat", 0, 8);
	setTexture("../Resource/Texture/Lucifer/LuciferHeartBeat-Sheet.png", 1, 8, 0);
	getAnimationComponent()->setState("heartbeat");


	//cout << "made heartbeat" << endl;
}