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
	cout << "T: Switch To Terrain Editing" << endl;
	cout << "P: Place Player" << endl;
	cout << "E: Place Enemy" << endl;
	cout << "Enter: Start Game" << endl;
	cout << "Escape: Editing Mode" << endl;

	Initialise(SCREEN_W, SCREEN_H, false, "Offline");
	AddFont("./fonts/feisarv5.fnt");

	state = GS_LEVEL_SETUP;	
	

	terrain = new Terrain(SCREEN_W / 16, SCREEN_H / 16);
	player = new Player(terrain);
	enemyList = new EnemyList();

	AddInputListener(this);
	AddInputListener(terrain);
}


GameController::~GameController()
{
}

void GameController::KeyStroke(SDL_Keycode key_)
{
	if (state == GS_LEVEL_SETUP)
	{
		if (key_ == SDLK_t)
		{
			ReplaceInputListener(terrain, 1);
			cout << "0: Select Grass Tile" << endl;
			cout << "1: Select Tree Tile" << endl;
			cout << "2: Select Wall Tile" << endl;
			cout << "3: Select Floor Tile" << endl;
			cout << "4: Select Door Tile" << endl;
			cout << "5: Select Water Tile" << endl;
		}

		if (key_ == SDLK_p)
		{
			ReplaceInputListener(player, 1);
			cout << "Left click to place player" << endl;
		}
		if (key_ == SDLK_e)
		{
			ReplaceInputListener(enemyList, 1);
			cout << "Left click to add enemy" << endl;
		}

		if (key_ == SDLK_RETURN || key_ == SDLK_RETURN2 )
		{
			state = GS_PLAY;
			player->SetPlaying(true);
			ReplaceInputListener(player, 1);
			cout << "Game Started" << endl;
			cout << "Press Escape to go back to editing mode" << endl;
		}
	}

	if (state == GS_PLAY)
	{
		if (key_ == SDLK_ESCAPE)
		{
			state = GS_LEVEL_SETUP;
			player->SetPlaying(false);
			cout << "Editing Mode" << endl;
			cout << "------------" << endl;
			cout << "T: Switch To Terrain Editing" << endl;
			cout << "P: Place Player" << endl;
			cout << "E: Place Enemy" << endl;
			cout << "Enter: Start Game" << endl;
		}
	}
}

void GameController::MouseClick(int mouseButton)
{}

void GameController::Run()
{
	float delta;
	//SDL_Texture* playerTexture = CreateSprite("./resources/images/player.png", 16, 16);
	do
	{
		delta = GetDeltaTime();

		//enemy updates
		if (state == GS_PLAY)
		{
			enemyList->Update(delta);
			player->Update(delta);
			enemyList->Update(delta);
		}

		//draw calls
		terrain->Draw();
		player->Draw();
		enemyList->Draw();

	} while (!FrameworkUpdate());
}