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

void SetupGame::LoadGameObjects(int levelID_, Terrain* &terrainOut_, Player* &playerOut_, EnemyList* &enemyListOut_)
{
	//create the shell game objects on the heap. then we fill
	terrainOut_ = new Terrain(SCREEN_W / TILE_SIZE, SCREEN_H / TILE_SIZE);
	playerOut_ = new Player(terrainOut_);
	enemyListOut_ = new EnemyList(terrainOut_, playerOut_);

	DatabaseManager dm;
	char * error = nullptr;
	
	//get the tbl_level data
	string whereStmt = "ID = " + ToString(levelID_);
	dm.Select(DB_STR, "tbl_level", "*", whereStmt, "", error);

	//should only ever be one row
	if (dm.Rows() != 1)
	{
		cout << "something went wrong selecting tbl_level. WHERE = " << whereStmt;
		return;
	}
	else
	{
		int playerRow = dm.GetValueInt(0, "player_row");
		int playerCol = dm.GetValueInt(0, "player_col");
		playerOut_->SetStartingPos(playerRow, playerCol);
	}


	//get the tbl_tile data
	whereStmt = "level_id = " + ToString(levelID_);
	dm.Select(DB_STR, "tbl_tile", "*", whereStmt, "", error);
	


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

	//get player row and col
	TerrainTile* playerTile = terrain_->TileAtMouseCoords(player_->Pos());
	string playerCol = ToString(playerTile->col);
	string playerRow = ToString(playerTile->row);
	 
	//insert the level record and retreive the ID
	vector<string> lvlColNames{ "player_row", "player_col" };
	vector<string> lvlValues{ playerRow, playerCol };
	int levelID = dm.Insert(DB_STR, "tbl_level", lvlColNames, lvlValues, error);
	
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



