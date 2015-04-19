//Enemy.h

#pragma once

#include "Vector.h"
#include "GLAHGraphics.h"
#include <vector>
#include "Terrain.h"
#include "InputListener.h"



class Enemy
{
public:

	Enemy();
	~Enemy();

	void SetPos(int x_, int y_);
	void SetTexture(SDL_Texture* texture_);
	Vector2 Pos();

private:	
	
	//TODO: Make this static
	SDL_Texture* enemyTexture;
	
	Vector2 pos;
	std::vector<TerrainTile*> path;
	bool loopPath;
};

class EnemyList : public InputListener
{
public:
	EnemyList();
	~EnemyList();
	void Draw();
	void Update(float delta_);
	void CreateEnemy(int x_, int y_);
	void UserInputGameSetup();
	
	//InputListener interface requirement
	virtual void KeyStroke(SDL_Keycode key_);
	virtual void MouseClick(int mouseButton);

private:
	std::vector<Enemy> enemyList;
	SDL_Texture * texture;
};