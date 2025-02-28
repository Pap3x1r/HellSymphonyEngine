#include "ZizGroundSlamState.h"

ZizGroundSlamState* ZizGroundSlamState::instance = nullptr;

ZizGroundSlamState* ZizGroundSlamState::getInstance() {
	if (!instance) {
		instance = new ZizGroundSlamState();
	}

	return instance;
}

void ZizGroundSlamState::enter(Boss* boss) {

}

void ZizGroundSlamState::update(Boss * boss, float dt){

}

void ZizGroundSlamState::exit(Boss* boss) {

}