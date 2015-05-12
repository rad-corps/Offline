#pragma once

#include "Enemy.h"
#include "Terrain.h"
#include "Player.h"
#include "InputListener.h"
#include "GLText.h"

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
	//used when in level creation mode
	GameController();

	//used when in level load mode
	GameController(Player* player_, Terrain* terrain_, EnemyList* enemyList_);
	
	//destructor
	~GameController();

	void Run();

	//InputListener interface requirements
	void KeyStroke(SDL_Keycode key_);
	void MouseClick(int mouseButton_);
	void MouseDown(int mouseButton_){}

private:
	//USER_INPUT_SWITCH inputSwitch;
	GAME_STATE state;
	
	GLText sampleText;
	
	Player* player;
	Terrain* terrain;
	EnemyList* enemyList;

};

