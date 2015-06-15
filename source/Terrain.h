#pragma once

#include <map>
#include <vector>
#include "SDL2/SDL.h"
#include "GLAHGraphics.h"
#include "Vector.h"
#include "InputListener.h"
#include "CONSTS.h"
#include <set>

enum TERRAIN_TILE_TYPE
{
	GRASS,
	TREE,
	BUILDING_WALL,
	BUILDING_FLOOR,
	DOOR,
	WATER
	//GOAL
};



struct TerrainTile
{
	TERRAIN_TILE_TYPE type;
	int col, row;
	int g, f;
	//int cost;
	TerrainTile* parent;

	int Cost()
	{
		switch (type)
		{
			case GRASS :		return 1;
			case TREE : 		return 2;
			case BUILDING_WALL: return 9999999;
			case BUILDING_FLOOR: return 1;
			case DOOR:			return 9999999;
			case WATER:			return 5;
			//case GOAL:			return 1;
		}
		return 0;
	}

	void Reset()
	{
		g = 99999999;
		f = 99999999;
		parent = nullptr;
	}

	Vector2 Pos()
	{
		return Vector2(col * TILE_SIZE, row * TILE_SIZE);
	}

	TerrainTile(int col_, int row_, TERRAIN_TILE_TYPE type_)
	{
		type = type_; 
		col = col_;
		row = row_;		

		Reset();
	}
};

std::ostream& operator<<(std::ostream& os, const TerrainTile* tile_);

class Terrain : public InputListener
{
public:
	Terrain(int w_, int h_);
	~Terrain();

	void Update(float delta_);
	void Draw();
	void SetTileDrawType(TERRAIN_TILE_TYPE type_);
	TerrainTile* TileAtDirection(TerrainTile* origin_, Vector2 dir_, int distance_ = 1);
	TerrainTile* TileAt(int row_, int col_);
	
	TerrainTile* TileAtMouseCoords(int x_, int y_);
	TerrainTile* TileAtMouseCoords(Vector2 pos_);
	std::vector<TerrainTile*> Edges(TerrainTile* tile_);
	std::vector<TerrainTile*> ShortestPath(TerrainTile* origin_, TerrainTile* dest_);

	std::vector<TerrainTile*> ClosestUnmonitoredTile(TerrainTile* origin_, std::set<TerrainTile*> monitoredTiles_);

	//InputListener interface requirement
	virtual void KeyStroke(SDL_Keycode key_);
	virtual void MouseClick(int mouseButton);
	virtual void MouseDown(int mouseButton);

	int Rows();
	int Cols();
private:
	int Heuristic(TerrainTile* origin_, TerrainTile* dest_);
	void Draw(TERRAIN_TILE_TYPE type_, int row_, int col_);
	std::vector<std::vector<TerrainTile*>> tileArray;
	void SetTerrain(std::vector<TerrainTile*> tiles_, TERRAIN_TILE_TYPE type_);


	SDL_Texture* textureGrass;
	SDL_Texture* textureWall;
	SDL_Texture* textureFloor;
	SDL_Texture* textureTrees;
	SDL_Texture* textureWater;
	SDL_Texture* textureDoor;
	//SDL_Texture* textureGoal;

	TERRAIN_TILE_TYPE drawType;
	//bool findingPath; //do not perform a search while one is in progress. 

	int rows;
	int cols;
};

