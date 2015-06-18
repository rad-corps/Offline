#pragma once

#include "GLAHGraphics.h"
#include "Vector.h"
#include "Terrain.h"
#include <vector>
#include "InputListener.h"
#include "Goal.h"
#include "Bullet.h"
#include <set>

enum PLAYER_UPDATE_STATE
{
	PUS_NORMAL,
	PUS_DIED,
	PUS_WON
};

enum PLAYER_BEHAVIOUR
{
	SEEK,
	FLEE,
	//WAIT
};

class Player : public InputListener
{
public:
	Player(Terrain* terrain_);
	~Player();

	PLAYER_UPDATE_STATE Update(float delta_, Goal* goal_, std::vector<Bullet> bullets_, std::set<TerrainTile*> monitoredTiles_);
	void Draw();
	void UserInputGameSetup();
	void UserInput(Terrain* terrain_);
	void SetPlaying(bool playing_);
	void SetStartingPos(int row_, int col_);

	void PursuitNotification();

	Vector2 Pos();

	//InputListener interface requirement
	virtual void KeyStroke(SDL_Keycode key_);
	virtual void MouseClick(int mouseButton);
	virtual void MouseDown(int mouseButton){}

private:
	Rect rect;
	Vector2 pos;
	SDL_Texture* playerTexture;
	std::vector<TerrainTile*> navigationList;
	Terrain* terrain;
	bool playing;
	bool spotted;
	float playerWaitTimer;
	std::vector<SDL_Texture*> textures;
	float animationTimer;
	int animSwitch;

	PLAYER_BEHAVIOUR behaviour;
};

