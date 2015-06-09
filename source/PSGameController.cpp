#include "PSGameController.h"
#include "PSMainMenu.h"
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
	cout << "Editing Mode" << endl;
	cout << "----------------------------" << endl;
	cout << "T: Switch To Terrain Editing" << endl;
	cout << "P: Place Player" << endl;
	cout << "E: Place Enemy" << endl;
	cout << "G: Place Goal" << endl;
	cout << "Enter: Begin Simulation" << endl;
	//cout << "Escape: Editing Mode" << endl;

	state = GS_LEVEL_SETUP;	
	
	terrain = new Terrain(SCREEN_W / TILE_SIZE, SCREEN_H / TILE_SIZE);
	player = new Player(terrain);
	goal = new Goal();

	enemyList = new EnemyList(terrain, player);

	//sampleText.SetText("test text");
	//sampleText.SetPos(Vector2(100, 100));
	initialised = false;
	promptText.SetPos(Vector2(SCREEN_W*0.5, SCREEN_H*0.5));
	promptText.SetAlignment(ALIGN_CENTRE);

	gameText.SetPos(Vector2(SCREEN_W*0.5, 100));
	gameText.SetAlignment(ALIGN_CENTRE);

	enteringLevelName = false;

	gameFinishTimer = 0.0f; 

	enemyList->SetBulletListener(this);
}

PSGameController::PSGameController(Player* player_, Terrain* terrain_, EnemyList* enemyList_, Goal* goal_)
{
	terrain = terrain_;
	player = player_;
	goal = goal_;
	enemyList = enemyList_;
	player->SetPlaying(true);
	state = GS_PLAY;
	initialised = false;
	enteringLevelName = false;

	promptText.SetPos(Vector2(SCREEN_W*0.5, SCREEN_H*0.5));
	promptText.SetAlignment(ALIGN_CENTRE);

	gameText.SetPos(Vector2(SCREEN_W*0.5, 100));
	gameText.SetAlignment(ALIGN_CENTRE);

	gameFinishTimer = 0.0f;
	enemyList->SetBulletListener(this);
}

PSGameController::PSGameController(int levelID_)
{
	SetupGame::LoadGameObjects(levelID_, terrain, player, enemyList, goal);
	state = GS_PLAY;
	player->SetPlaying(true);
	initialised = false;
	enteringLevelName = false;

	promptText.SetPos(Vector2(SCREEN_W*0.5, SCREEN_H*0.5));
	promptText.SetAlignment(ALIGN_CENTRE);

	gameText.SetPos(Vector2(SCREEN_W*0.5, 100));
	gameText.SetAlignment(ALIGN_CENTRE);

	gameFinishTimer = 0.0f;
	enemyList->SetBulletListener(this);
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

void PSGameController::ShootBullet(Vector2 pos_, Vector2 dir_)
{
	Bullet bullet;
	bullet.Shoot(pos_, dir_);
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
				if (SetupGame::SaveLevel(terrain, player, enemyList, levelName, goal))
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
			//cout << "6: Select Goal Tile" << endl;
		}

		if (key_ == SDLK_p)
		{
			ReplaceInputListener(player, 1);
			cout << "Left click to place player" << endl;
		}
		if (key_ == SDLK_g)
		{
			ReplaceInputListener(goal, 1);
			cout << "Left click to place goal" << endl;
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
			cout << "G: Place Goal" << endl;
			cout << "Enter: Begin Simulation" << endl;
		}
	}
}

void PSGameController::MouseClick(int mouseButton)
{}

ProgramState* PSGameController::Update(float delta_)
{
	if (!initialised)
		Init();

	//dont update game objects after game completion
	if (pus == PUS_WON || pus == PUS_DIED)
	{		
		gameFinishTimer += delta_;
		if (gameFinishTimer > 3.0f)
		{
			//must cleanup before destructor using this pattern. 
			NullifyInputListeners();
			ClearInputListeners();

			return new PSMainMenu();
		}
		return nullptr;
	}


	if (state == GS_PLAY)
	{
		enemyList->Update(delta_);
		pus = player->Update(delta_, goal);
		if (pus == PUS_WON) //player won the game, start a timer, display success screen, back to menu
		{
			gameText.SetText("Player Success");			
		}
		else if (pus == PUS_DIED) //player lost game, start a timer, display failure, back to menu
		{
			gameText.SetText("Player Failure");
		}
			
	}
	return nullptr;
}

void PSGameController::Draw()
{
	//draw calls
	terrain->Draw();
	goal->Draw();
	player->Draw();
	enemyList->Draw();
	//sampleText.Draw();
	promptText.Draw();
	gameText.Draw();
}