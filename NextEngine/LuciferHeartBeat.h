#pragma once
#include "TexturedObject.h"

class LuciferHeartBeat : public TexturedObject{

	static LuciferHeartBeat* instance;

public:
	LuciferHeartBeat();
	static LuciferHeartBeat* getInstance();

	

};