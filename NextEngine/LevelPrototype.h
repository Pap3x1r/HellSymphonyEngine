#pragma once
#include "Level.h"
#include "Player.h"
#include "Enemy.h"

#include "Sword.h"
#include "Bow.h"
#include "Shield.h"

#include "QTEManager.h"

#include <list>

class LevelPrototype : public Level
{
private:
	float timeK = 0;
	float dt = 0;
	list<DrawableObject*> objectsList;
	Enemy* enemy;
	Player* player;
	Sword* sword;
	Bow* bow;
	Shield* shield;
	QTEManager* qteManager;
	//UI
	SimpleObject* playerHealthBar;
	SimpleObject* playerUltimateBar;
	SimpleObject* witherHealthBar;
	int d = 0;
	int row = 0;
	int col = 0;
public:
	virtual void levelLoad();
	virtual void levelInit();
	virtual void levelUpdate();
	virtual void levelDraw();
	virtual void levelFree();
	virtual void levelUnload();

	virtual void handleKey(char key);
	virtual void handleMouse(int type, int x, int y);
	virtual void handleAnalogStick(int type, float amount);

	virtual void addObject(DrawableObject* obj) override;
	Player* getPlayer() const;
	void savePlayerData(const Player* player, const std::string& filename);
	Player* loadPlayerData(const string& filepath);
	void Phase1QTE();
};
