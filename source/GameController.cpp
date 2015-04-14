#include "GameController.h"
#include "DatabaseManager.h"
#include <time.h>
#include <iostream>
#include <string>
#include <iostream>
#include "GLAHGraphics.h"
#include "Terrain.h"
#include "Player.h"

using namespace std;
#define INVADERS_FONT "./fonts/feisarv5.fnt"
#define SCREEN_W 1024
#define SCREEN_H 768

GameController::GameController()
{
	//randomize seed
	srand((unsigned int)time(NULL));

	//instructions
	cout << "0: Place Grass Tile" << endl;
	cout << "1: Place Tree Tile" << endl;
	cout << "2: Place Wall Tile" << endl;
	cout << "3: Place Floor Tile" << endl;
	cout << "4: Place Door Tile" << endl;
	cout << "5: Place Water Tile" << endl;
	cout << "P: Place Player" << endl;
	cout << "E: Place Enemy" << endl;
	cout << "Enter: Start Game" << endl;

	Initialise(SCREEN_W, SCREEN_H, false, "Offline");
	AddFont("./fonts/feisarv5.fnt");

	inputSwitch = INPUT_TERRAIN;

	state = GS_LEVEL_SETUP;	
}


GameController::~GameController()
{
}

void GameController::Run()
{

	Terrain terrain(SCREEN_W / 16, SCREEN_H / 16);
	Player player;

	float delta;
	//SDL_Texture* playerTexture = CreateSprite("./resources/images/player.png", 16, 16);
	do
	{
		//switch user input switch
		if (IsKeyDown(SDLK_0)
			|| IsKeyDown(SDLK_1)
			|| IsKeyDown(SDLK_2)
			|| IsKeyDown(SDLK_3)
			|| IsKeyDown(SDLK_4)
			|| IsKeyDown(SDLK_5))
		{
			inputSwitch = INPUT_TERRAIN;
		}

		if (IsKeyDown(SDLK_0))
			terrain.SetTileDrawType(GRASS);
		if (IsKeyDown(SDLK_1))
			terrain.SetTileDrawType(TREE);
		if (IsKeyDown(SDLK_2))
			terrain.SetTileDrawType(BUILDING_WALL);
		if (IsKeyDown(SDLK_3))
			terrain.SetTileDrawType(BUILDING_FLOOR);
		if (IsKeyDown(SDLK_4))
			terrain.SetTileDrawType(DOOR);
		if (IsKeyDown(SDLK_5))
			terrain.SetTileDrawType(WATER);

		if (IsKeyDown(SDLK_p))
		{
			inputSwitch = INPUT_PLAYER;
		}
		if (IsKeyDown(SDLK_e))
		{
			inputSwitch = INPUT_ENEMIES;
		}
		if (IsKeyDown(SDLK_RETURN) || IsKeyDown(SDLK_RETURN2))
		{
			state = GS_PLAY;
		}

		delta = GetDeltaTime();

		//terrain updates
		terrain.Update(delta);
		if (inputSwitch == INPUT_TERRAIN)
			terrain.UserInput();
		
		//player updates
		player.Update(delta);
		if (inputSwitch == INPUT_PLAYER && state == GS_LEVEL_SETUP)
		{
			player.UserInputGameSetup();
		}

		//draw calls
		terrain.Draw();
		player.Draw();
	} while (!FrameworkUpdate());
}