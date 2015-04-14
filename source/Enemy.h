//Enemy.h

#pragma once

#include "Vector.h"
#include "GLAHGraphics.h"
#include <vector>
#include "Terrain.h"



class Enemy
{
public:

	Enemy();
	~Enemy();

	void SetPos(int x_, int y_);
	void SetTexture(SDL_Texture* texture_);
	void UserInputGameSetup();
	Vector2 Pos();

private:	
	
	//TODO: Make this static
	SDL_Texture* enemyTexture;
	
	Vector2 pos;
	std::vector<TerrainTile*> path;
	bool loopPath;
};

class EnemyList
{
public:
	EnemyList();
	~EnemyList();

	void CreateEnemy(int x_, int y_);
	void UserInput();
	void Draw();
	void Update(float delta_);


private:
	std::vector<Enemy> enemyList;
	SDL_Texture * texture;
};