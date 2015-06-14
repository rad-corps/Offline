#pragma once

#include "Enemy.h"
#include "Terrain.h"
#include "Player.h"
#include "Goal.h"
#include "InputListener.h"
#include "GLText.h"
#include "ProgramState.h"
#include "Bullet.h"

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

class PSGameController : public InputListener, public ProgramState, public BulletListener
{
public:
	//used when in level creation mode
	PSGameController();

	//used when in level load mode
	PSGameController(Player* player_, Terrain* terrain_, EnemyList* enemyList_, Goal* goal_ = nullptr);
	PSGameController(int levelID_);
	
	//destructor
	virtual ~PSGameController();

	//ProgramState interface Req
	virtual ProgramState* Update(float delta);
	virtual void Draw();

	//BulletListener Interface Req
	virtual void ShootBullet(Vector2 pos_, Vector2 dir_);


	//InputListener interface requirements
	void KeyStroke(SDL_Keycode key_);
	void MouseClick(int mouseButton_);
	void MouseDown(int mouseButton_){}

private:
	void Init();
	//USER_INPUT_SWITCH inputSwitch;
	GAME_STATE state;
	
	GLText sampleText;
	GLText promptText;
	GLText gameText;

	bool enteringLevelName;
	std::string levelName;
	
	Goal* goal;
	Player* player;
	PLAYER_UPDATE_STATE pus;
	Terrain* terrain;
	EnemyList* enemyList;
	std::vector<Bullet> bullets;

	//can not initialise inputListeners in the constructor as it will have side effects from where the constructor is called. 
	bool initialised;
	float gameFinishTimer;

};

