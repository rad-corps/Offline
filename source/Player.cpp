#include "Player.h"
#include <iostream>

using namespace std;

Player::Player()
{
	playerTexture = CreateSprite("./resources/images/player.png", 16, 16);
}


Player::~Player()
{
}


void Player::UserInputGameSetup()
{
	int mouseX, mouseY;
	GetMouseLocation(mouseX, mouseY);

	//check for mouse left click (src)
	if (GetMouseButtonDown(0))
	{
		pos.x = mouseX;
		pos.y = mouseY;

		pos.x = (int)(pos.x / 16);
		pos.y = (int)(pos.y / 16);;

		pos.x *= 16;
		pos.y *= 16;
	}
}

void Player::UserInput(Terrain* terrain_)
{
	int mouseX, mouseY;
	GetMouseLocation(mouseX, mouseY);

	//check for mouse left click (src)
	if (GetMouseButtonDown(0))
	{
		//convert click location to tile
		TerrainTile* dstTile = terrain_->TileAtMouseCoords(mouseX, mouseY);

		//convert player location to tile
		TerrainTile* playerTile = terrain_->TileAtMouseCoords(static_cast<int>(pos.x), static_cast<int>(pos.y));

		//get the vector of tiles to nav to 
		navigationList = terrain_->ShortestPath(playerTile, dstTile);
	}
}

void Player::Draw()
{
	MoveSprite(playerTexture, pos.x, pos.y);
	DrawSprite(playerTexture);
}

void Player::Update(float delta_)
{
	//while the navigationList is not empty. 
	if (!navigationList.empty())
	{
		//get the next node and move towards it
		TerrainTile* nextNode = navigationList[navigationList.size()-1];
		Vector2 nextNodePos = nextNode->Pos();

		//if reached pop it off the top
		if ((pos - nextNode->Pos()).GetMagnitude() < 1.0f)
		{
			cout << "node reached, removing" << endl;
			navigationList.erase(navigationList.end() - 1);
		}
		else
		{
			//TODO FIX - .GetNormal does not work on vector with Magnitude of 0
			Vector2 direction = (nextNodePos - pos).GetNormal();
			pos += direction;
		}
	}
}