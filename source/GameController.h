#pragma once

enum USER_INPUT_SWITCH
{
	INPUT_PLAYER,
	INPUT_TERRAIN,
	INPUT_ENEMIES
};

class GameController
{
public:
	GameController();
	~GameController();

	void Run();

private:
	USER_INPUT_SWITCH inputSwitch;
};

