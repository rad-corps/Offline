#include "PSGameController.h"
#include "DatabaseManager.h"
#include "SetupGame.h"
#include <iostream>
#include <string>
#include <iostream>
#include "GLAHGraphics.h"
#include "Terrain.h"
#include "Player.h"
#include "CONSTS.h"

using namespace std;


PSGameController::PSGameController()
{
	//instructions
	cout << "T: Switch To Terrain Editing" << endl;
	cout << "P: Place Player" << endl;
	cout << "E: Place Enemy" << endl;
	cout << "Enter: Start Game" << endl;
	cout << "Escape: Editing Mode" << endl;

	state = GS_LEVEL_SETUP;	
	
	terrain = new Terrain(SCREEN_W / TILE_SIZE, SCREEN_H / TILE_SIZE);
	player = new Player(terrain);
	enemyList = new EnemyList(terrain, player);

	AddInputListener(this);
	AddInputListener(terrain);

	sampleText.SetText("test text");
	sampleText.SetPos(Vector2(100, 100));
}

PSGameController::PSGameController(Player* player_, Terrain* terrain_, EnemyList* enemyList_)
{
	terrain = terrain_;
	player = player_;
	enemyList = enemyList_;

	state = GS_PLAY;
	AddInputListener(this);
	AddInputListener(player);
}

PSGameController::~PSGameController()
{
	delete terrain;
	delete player;
	delete enemyList;
}



void PSGameController::KeyStroke(SDL_Keycode key_)
{
	if (state == GS_LEVEL_SETUP)
	{
		//save the terrain, player and enemies
		if (key_ == SDLK_s)
		{
			SetupGame::SaveLevel(terrain, player, enemyList);
		}
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

void PSGameController::MouseClick(int mouseButton)
{}

ProgramState* PSGameController::Update(float delta_)
{
	if (state == GS_PLAY)
	{
		enemyList->Update(delta_);
		player->Update(delta_);
	}

	return nullptr;
}

void PSGameController::Draw()
{
	//draw calls
	terrain->Draw();
	player->Draw();
	enemyList->Draw();
	sampleText.Draw();
}