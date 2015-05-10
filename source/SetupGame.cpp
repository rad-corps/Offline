#include "SetupGame.h"
#include "DatabaseManager.h"
#include <iostream>
#include <sstream>
#include "FrameworkHelpers.h"

using namespace std;

SetupGame::SetupGame()
{
}


SetupGame::~SetupGame()
{
}

void SetupGame::CreateGameObjects(int levelID_, Terrain* &terrainOut_, Player* &playerOut_, EnemyList* &enemyListOut_)
{
	DatabaseManager dm;
	char * error = nullptr;
	string whereStmt = "level_id = " + ToString(levelID_);
	dm.Select(DB_STR, "tbl_tile", "*", whereStmt, "", error);
	
	terrainOut_ = new Terrain(SCREEN_W / TILE_SIZE, SCREEN_H / TILE_SIZE);
	playerOut_ = new Player(terrainOut_);
	enemyListOut_ = new EnemyList(terrainOut_, playerOut_);

	//get the info out of the db and plonk it into terrainOut_
	for (int dbRow = 0; dbRow < dm.Rows(); ++dbRow)
	{
		int type = dm.GetValueInt(dbRow, "type");
		int row = dm.GetValueInt(dbRow, "row");
		int col = dm.GetValueInt(dbRow, "col");
		terrainOut_->TileAt(row, col)->type = (TERRAIN_TILE_TYPE)type;		
	}
}

void SetupGame::DBTest1()
{
	DatabaseManager dm;
	char * error = nullptr;
	vector<string> emptyVec;
	dm.Insert(DB_STR, "tbl_level", emptyVec, emptyVec, error);
}

void SetupGame::SaveLevel(Terrain* terrain_, Player* player_, EnemyList* enemyList_)
{
	//setup the DatabaseManager object
	DatabaseManager dm;
	char * error = nullptr;

	//insert the level record and retreive the ID
	vector<string> emptyVec;
	int levelID = dm.Insert(DB_STR, "tbl_level", emptyVec, emptyVec, error);
	
	//create all the terrain tiles
	for (int col = 0; col < terrain_->Cols(); ++col)
	{
		for (int row = 0; row < terrain_->Rows(); ++row)
		{
			//the tile to save
			TerrainTile* tile = terrain_->TileAt(row, col);
			
			//convert all values to strings
			string levelIDStr = ToString(levelID);
			string typeStr = ToString((int)tile->type);
			string rowStr = ToString(row);
			string colStr = ToString(col);

			//setup the colNames
			vector<string> colNames{"level_id", "type", "row", "col"};
			
			//setup the values
			vector<string> values{ levelIDStr, typeStr, rowStr, colStr };

			//get row, col, type, level id and insert
			dm.Insert(DB_STR, "tbl_tile", colNames, values, error);
		}
	}
}



