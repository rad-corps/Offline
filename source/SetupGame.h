#pragma once

#include "Terrain.h"
#include "Player.h"
#include "Enemy.h"

class SetupGame
{
private:
	SetupGame();

public:
	~SetupGame();

	//pass nullptrs to this function and they will be created ready for use by the GameController
	static void LoadGameObjects(int levelID_, Terrain* &terrainOut_, Player* &playerOut_, EnemyList* &enemyListOut_);
	static void DBTest1();
	static void SetupGame::SaveLevel(Terrain* terrain_, Player* player_, EnemyList* enemyList_);

};

