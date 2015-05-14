#pragma once

#include "Enemy.h"
#include "Terrain.h"
#include "Player.h"
#include "InputListener.h"
#include "GLText.h"
#include "ProgramState.h"

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

class PSGameController : public InputListener, public ProgramState
{
public:
	//used when in level creation mode
	PSGameController();

	//used when in level load mode
	PSGameController(Player* player_, Terrain* terrain_, EnemyList* enemyList_);
	PSGameController(int levelID_);
	
	//destructor
	virtual ~PSGameController();

	virtual ProgramState* Update(float delta);
	virtual void Draw();


	//InputListener interface requirements
	void KeyStroke(SDL_Keycode key_);
	void MouseClick(int mouseButton_);
	void MouseDown(int mouseButton_){}

private:
	void Init();
	//USER_INPUT_SWITCH inputSwitch;
	GAME_STATE state;
	
	GLText sampleText;
	
	Player* player;
	Terrain* terrain;
	EnemyList* enemyList;

	//can not initialise inputListeners in the constructor as it will have side effects from where the constructor is called. 
	bool initialised;

};

