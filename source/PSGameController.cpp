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

	//sampleText.SetText("test text");
	//sampleText.SetPos(Vector2(100, 100));
	initialised = false;
	promptText.SetPos(Vector2(50, 50));
	promptText.SetAlignment(ALIGN_LEFT);
	enteringLevelName = false;
}

PSGameController::PSGameController(Player* player_, Terrain* terrain_, EnemyList* enemyList_)
{
	terrain = terrain_;
	player = player_;
	enemyList = enemyList_;
	state = GS_PLAY;
	initialised = false;
}

PSGameController::PSGameController(int levelID_)
{
	SetupGame::LoadGameObjects(levelID_, terrain, player, enemyList);
	state = GS_PLAY;
	initialised = false;
}

PSGameController::~PSGameController()
{
	delete terrain;
	delete player;
	delete enemyList;
}

void
PSGameController::Init()
{
	ClearInputListeners();
	AddInputListener(this);
	AddInputListener(player);
	initialised = true;
}

void PSGameController::KeyStroke(SDL_Keycode key_)
{


	if (state == GS_LEVEL_SETUP)
	{
		if (enteringLevelName)
		{
			if (key_ == SDLK_RETURN)
			{
				enteringLevelName = false;
				cout << "Saving Level" << endl;
				if (SetupGame::SaveLevel(terrain, player, enemyList, levelName))
				{
					cout << "Level save successful" << endl;
				}
				else
				{
					cout << "Something went wrong saving level" << endl;
				}
			}
			else
			{
				//capture keypresses
				levelName += char(key_);
				cout << levelName << endl;

				promptText.SetText("Enter Level Name: " + levelName);
			}
			return;
		}
		

		//save the terrain, player and enemies
		if (key_ == SDLK_s)
		{
			promptText.SetText("Enter Level Name: ");
			enteringLevelName = true;
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
	if (!initialised)
		Init();

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
	//sampleText.Draw();
	promptText.Draw();
}