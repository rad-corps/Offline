#pragma once

#include "Enemy.h"
#include "Terrain.h"
#include "Player.h"
#include "InputListener.h"

enum USER_INPUT_SWITCH
{
	INPUT_PLAYER,
	INPUT_TERRAIN,
	INPUT_ENEMIES
};

enum GAME_STATE
{
	GS_LEVEL_SETUP,
	GS_PLAY
};

class GameController : public InputListener
{
public:
	GameController();
	~GameController();

	void Run();

	void KeyStroke(SDL_Keycode key_);
	void MouseClick(int mouseButton_);
	void MouseDown(int mouseButton_){}

private:
	//USER_INPUT_SWITCH inputSwitch;
	GAME_STATE state;
	
	
	Player* player;
	Terrain* terrain;
	EnemyList* enemyList;

};

