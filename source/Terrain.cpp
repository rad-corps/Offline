#include "Terrain.h"
#include <iostream>

//std::map<TERRAIN_TILE_TYPE, SDL_Texture*> Terrain::textureMap;
using namespace std;

Terrain::Terrain()
{
	//init the textures
	textureGrass = CreateSprite("./resources/images/terrain_grass.png", 16, 16);
	textureWall = CreateSprite("./resources/images/terrain_wall.png", 16, 16);
	textureFloor = CreateSprite("./resources/images/terrain_floor.png", 16, 16);
	textureTrees = CreateSprite("./resources/images/terrain_tree.png", 16, 16);
	textureWater = CreateSprite("./resources/images/terrain_water.png", 16, 16);
	textureDoor = CreateSprite("./resources/images/terrain_door.png", 16, 16);


	for (int row = 0; row < 32; ++row)
	{
		vector<TerrainTile> v;
		tileArray.push_back(v);

		for (int col = 0; col < 32; ++col)
		{
			tileArray[row].push_back(TerrainTile());
		}
	}

	tileArray[1][1].type = BUILDING_WALL;
}

Terrain::~Terrain()
{
}

void Terrain::Draw(TERRAIN_TILE_TYPE type_, int row_, int col_)
{
	SDL_Texture* tempPtr = nullptr;

	switch (type_)
	{
		case GRASS:				tempPtr = textureGrass; break;
		case TREE:				tempPtr = textureTrees;	break;
		case BUILDING_WALL:		tempPtr = textureWall;	break;
		case BUILDING_FLOOR:	tempPtr = textureFloor;	break;
		case DOOR:				tempPtr = textureDoor;	break;
		case WATER:				tempPtr = textureWater;	break;
	}

	if (tempPtr == nullptr)
	{
		cout << "Unknown TERRAIN_TILE_TYPE in Terrain::Draw(TERRAIN_TILE_TYPE type_, int row_, int col_)" << endl;
		return;
	}

	MoveSprite(tempPtr, col_ * 16, row_ * 16);
	DrawSprite(tempPtr);
}

void Terrain::Draw()
{
	for (int row = 0; row < 32; ++row)
	{
		for (int col = 0; col < 32; ++col)
		{
			//get the type
			Draw(tileArray[row][col].type, row, col);
		}
	}
}
