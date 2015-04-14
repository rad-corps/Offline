#pragma once

#include <map>
#include <vector>
#include "SDL2/SDL.h"
#include "GLAHGraphics.h"

enum TERRAIN_TILE_TYPE
{
	GRASS,
	TREE,
	BUILDING_WALL,
	BUILDING_FLOOR,
	DOOR,
	WATER
};

struct TerrainTile
{
	TERRAIN_TILE_TYPE type;
	int col, row;
	int g, f;
	int cost;
	TerrainTile* parent;

	void Reset()
	{
		g = 99999999;
		f = 99999999;
		parent = nullptr;
	}

	TerrainTile(int col_, int row_, TERRAIN_TILE_TYPE type_)
	{
		type = type_; 
		col = col_;
		row = row_;		
		cost = 1; //TODO different for each unit and TERRAIN_TILE_TYPE

		Reset();
	}


};

class Terrain
{
public:
	Terrain();
	~Terrain();

	void Update(float delta_);
	void Draw();
	TerrainTile* TileAt(int row_, int col_);
	TerrainTile* TileAtMouseCoords(int x_, int y_);
	std::vector<TerrainTile*> Edges(TerrainTile* tile_);
	std::vector<TerrainTile*> ShortestPath(TerrainTile* origin_, TerrainTile* dest_);


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

	//bool findingPath; //do not perform a search while one is in progress. 
};

