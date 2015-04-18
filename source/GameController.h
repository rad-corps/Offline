#pragma once

#include "Enemy.h"

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

class GameController
{
public:
	GameController();
	~GameController();

	void Run();

private:
	USER_INPUT_SWITCH inputSwitch;
	GAME_STATE state;
	
};

