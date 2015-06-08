#include "Player.h"
#include <iostream>
#include "CONSTS.h"

using namespace std;

Player::Player(Terrain* terrain_)
{
	terrain = terrain_;
	playerTexture = CreateSprite("./resources/images/player.png", TILE_SIZE, TILE_SIZE);
	playing = false;
}


Player::~Player()
{
}

Vector2 Player::Pos()
{
	return pos;
}

void Player::SetStartingPos(int row_, int col_)
{
	pos.y = row_ * TILE_SIZE;
	pos.x = col_ * TILE_SIZE;
}

void Player::SetPlaying(bool playing_)
{
	playing = playing_;
}


void Player::UserInputGameSetup()
{

}

void Player::UserInput(Terrain* terrain_)
{

}

void Player::MouseClick(int mouseButton)
{
	//if (playing)
	//{
	//	//check for mouse left click (src)
	//	if (mouseButton == 1)
	//	{
	//		int mouseX, mouseY;
	//		GetMouseLocation(mouseX, mouseY);

	//		//convert click location to tile
	//		TerrainTile* dstTile = terrain->TileAtMouseCoords(mouseX, mouseY);

	//		//convert player location to tile
	//		TerrainTile* playerTile = terrain->TileAtMouseCoords(static_cast<int>(pos.x), static_cast<int>(pos.y));

	//		//get the vector of tiles to nav to 
	//		navigationList = terrain->ShortestPath(playerTile, dstTile);
	//	}
	//}
	/*else */if ( !playing ) //implies game setup
	{
		if (mouseButton == 1)
		{
			int mouseX, mouseY;
			GetMouseLocation(mouseX, mouseY);

			pos.x = mouseX;
			pos.y = mouseY;

			pos.x = (int)(pos.x / TILE_SIZE);
			pos.y = (int)(pos.y / TILE_SIZE);

			pos.x *= TILE_SIZE;
			pos.y *= TILE_SIZE;
		}
	}
}

void Player::KeyStroke(SDL_Keycode key_)
{}

void Player::Draw()
{
	MoveSprite(playerTexture, pos.x, pos.y);
	DrawSprite(playerTexture);
}

PLAYER_UPDATE_STATE Player::Update(float delta_, Goal* goal_)
{
	//while the navigationList is not empty. 
	if ( navigationList.empty())
	{
		//		//convert click location to tile
		TerrainTile* dstTile = terrain->TileAtMouseCoords(goal_->Pos());

		//convert player location to tile
		TerrainTile* playerTile = terrain->TileAtMouseCoords(static_cast<int>(pos.x), static_cast<int>(pos.y));

		//		//get the vector of tiles to nav to 
		navigationList = terrain->ShortestPath(playerTile, dstTile);
	}
	else if (!navigationList.empty())
	{
		//get the next node and move towards it
		TerrainTile* nextNode = navigationList[navigationList.size()-1];
		Vector2 nextNodePos = nextNode->Pos();

		//if reached pop it off the top
		if ((pos - nextNode->Pos()).GetMagnitude() < 16.0f)
		{
			pos = nextNode->Pos();
			navigationList.erase(navigationList.end() - 1);
		}
		else
		{
			//TODO FIX - .GetNormal does not work on vector with Magnitude of 0
			Vector2 direction = (nextNodePos - pos).GetNormal();
			Vector2 velocity = (direction * 200) * delta_;
			pos += velocity;
		}
	}

	if (terrain->TileAtMouseCoords(pos) == terrain->TileAtMouseCoords(goal_->Pos()))
	{
		return PUS_WON;
	}

	// if (IsKeyDown(SDLK_UP) || IsKeyDown(SDLK_w))
	// {		
	// 	pos.y -= 100 * delta_;
	// }
	// if (IsKeyDown(SDLK_DOWN) || IsKeyDown(SDLK_s))
	// {
	// 	pos.y += 100 * delta_;
	// }
	// if (IsKeyDown(SDLK_RIGHT) || IsKeyDown(SDLK_d))
	// {
	// 	pos.x += 100 * delta_;
	// }
	// if (IsKeyDown(SDLK_LEFT) || IsKeyDown(SDLK_a))
	// {
	// 	pos.x -= 100 * delta_;
	// }
	return PUS_NORMAL;
}