//Enemy.h

#pragma once

#include "Vector.h"
#include "GLAHGraphics.h"
#include <vector>
#include "Terrain.h"
#include "InputListener.h"
#include "Player.h"

enum EnemyBehaviour
{
	EB_PATROL,
	EB_PURSUE
};

class Enemy
{
	friend class EnemyList;
public:

	Enemy(Terrain* terrain_);
	~Enemy();

	void Update(float delta_);
	void SetPos(int x_, int y_);
	//void SetTexture(SDL_Texture* texture_);
	Vector2 Pos();
	void AddNode(TerrainTile* tile_);

private:	
	
	//TODO: Make this static
	SDL_Texture* enemyTexture;
	
	
	Vector2 pos;
	std::vector<TerrainTile*> goalNodes;
	int nextGoalNode;
	std::vector<TerrainTile*> navigationList;
	Terrain* terrain;
	bool loopPath;
	Vector2 direction;
	float animationTimer;
	int animSwitch;
	TerrainTile* currentTile;
	EnemyBehaviour behaviour;

};

class EnemyList : public InputListener
{
public:
	EnemyList(Terrain* terrain_, Player* player_);
	~EnemyList();
	void Draw();
	void Update(float delta_);
	void CreateEnemy(int x_, int y_);
	void UserInputGameSetup();
	
	//InputListener interface requirement
	virtual void KeyStroke(SDL_Keycode key_);
	virtual void MouseClick(int mouseButton);
	virtual void MouseDown(int mouseButton){}

private:
	void DrawViewFrustrum(Enemy* enemy_);
	bool addingNodes;
	std::vector<Enemy> enemyList;
	std::vector<SDL_Texture*> textures;
	//SDL_Texture * texture;
	SDL_Texture * nodeTexture;
	SDL_Texture * viewTexture;
	Terrain* terrain;
	SDL_Texture* currentTileTexture;

	Player* player;
};