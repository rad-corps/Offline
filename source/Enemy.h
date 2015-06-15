//Enemy.h

#pragma once

#include "Vector.h"
#include "GLAHGraphics.h"
#include <vector>
#include <set>
#include "Terrain.h"
#include "InputListener.h"
#include "Player.h"
#include "BulletListener.h"

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

	void SetBulletListener(BulletListener* bulletListener_);

	void Update(float delta_, Player* player_);
	void SetPos(int x_, int y_);
	//void SetTexture(SDL_Texture* texture_);
	Vector2 Pos();
	void AddNode(TerrainTile* tile_);
	
	//SetupGame Interface
	std::vector<TerrainTile*> GetGoalNodes();
	void AddGoalNode(TerrainTile* goalNode_);

private:	
	
	//TODO: Make this static
	SDL_Texture* enemyTexture;
	
	
	Vector2 pos;
	std::vector<TerrainTile*> goalNodes;
	int nextGoalNode;
	std::vector<TerrainTile*> navigationList;
	std::vector<TerrainTile*> viewableTiles;
	Terrain* terrain;
	bool loopPath;
	Vector2 direction;
	float animationTimer;
	int animSwitch;
	int currentTerrainCost;
	TerrainTile* currentTile;
	EnemyBehaviour behaviour;
	BulletListener* bulletListener;
	float reloadTime;

};

class EnemyList : public InputListener
{
public:
	EnemyList(Terrain* terrain_, Player* player_);
	~EnemyList();

	std::set<TerrainTile*> GetMonitoredTiles();

	void SetBulletListener(BulletListener* bulletListener_);
	void Draw();
	void Update(float delta_);
	void CreateEnemy(int x_, int y_);
	void UserInputGameSetup();
	
	//InputListener interface requirement
	virtual void KeyStroke(SDL_Keycode key_);
	virtual void MouseClick(int mouseButton);
	virtual void MouseDown(int mouseButton){}

	//interface for SetupGame
	std::vector<Enemy> GetEnemyList();
	void AddEnemy(Enemy enemy_);


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
	BulletListener* bulletListener;

	Player* player;
};