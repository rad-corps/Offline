#pragma once

#include "Terrain.h"
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"
#include "BulletListener.h"

class SetupGame
{
private:
	SetupGame();

public:
	~SetupGame();

	//pass nullptrs to this function and they will be created ready for use by the GameController
	static void LoadGameObjects(int levelID_, Terrain* &terrainOut_, Player* &playerOut_, EnemyList* &enemyListOut_, Goal* &goal_, BulletListener* bulletListener_);
	static void DBTest1();
	static bool SaveLevel(Terrain* terrain_, Player* player_, EnemyList* enemyList_, std::string levelName_, Goal* goal_);

};

