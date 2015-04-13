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

	TerrainTile(){ type = GRASS;  }
	TerrainTile(TERRAIN_TILE_TYPE type_){ type = type_; }
};

class Terrain
{
public:
	Terrain();
	~Terrain();
	void Draw();


private:
	void Draw(TERRAIN_TILE_TYPE type_, int row_, int col_);
	std::vector<std::vector<TerrainTile>> tileArray;

	SDL_Texture* textureGrass;
	SDL_Texture* textureWall;
	SDL_Texture* textureFloor;
	SDL_Texture* textureTrees;
	SDL_Texture* textureWater;
	SDL_Texture* textureDoor;
};

