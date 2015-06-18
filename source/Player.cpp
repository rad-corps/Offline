//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
/////////////////////////////////////////////////////////////////////////

#include "Player.h"
#include <iostream>
#include "CONSTS.h"
#include "Collision.h"

using namespace std;

Player::Player(Terrain* terrain_)
{
	terrain = terrain_;
	//playerTexture = CreateSprite("./resources/images/player.png", TILE_SIZE, TILE_SIZE);
	playerTexture = nullptr;
	textures.push_back(CreateSprite("./resources/images/player1.png", TILE_SIZE, TILE_SIZE));
	textures.push_back(CreateSprite("./resources/images/player2.png", TILE_SIZE, TILE_SIZE));
	playing = false;
	rect.height = TILE_SIZE;
	rect.width = TILE_SIZE;
	rect.centre = Vector2(0, 0);
	spotted = false;
	behaviour = SEEK;
	playerWaitTimer = 0.0f;
	animationTimer = 0.0f;
	animSwitch = 0;
}


Player::~Player()
{
}

void Player::PursuitNotification()
{
	spotted = true;
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

PLAYER_UPDATE_STATE Player::Update(float delta_, Goal* goal_, std::vector<Bullet> bullets_, std::set<TerrainTile*> monitoredTiles_)
{
	playerWaitTimer += delta_;
	animationTimer += delta_;

	//set animation
	if (animationTimer > 0.6f)
	{
		animationTimer = 0.0f;
		animSwitch++;

		if (animSwitch % 2 == 0)
		{
			playerTexture = textures[0];
		}
		else
		{
			playerTexture = textures[1];
		}
	}




	if (spotted && behaviour != FLEE)
	{
		cout << "behaviour == FLEE" << endl;
		behaviour = FLEE;
		navigationList.clear();
		
		spotted = false;
	}

	//update player on normal path 
	//while the navigationList is not empty. 
	if (navigationList.empty() && behaviour == SEEK)
	{
		//		//convert click location to tile
		TerrainTile* dstTile = terrain->TileAtMouseCoords(goal_->Pos());

		//convert player location to tile
		TerrainTile* playerTile = terrain->TileAtMouseCoords(static_cast<int>(pos.x), static_cast<int>(pos.y));

		//		//get the vector of tiles to nav to 
		navigationList = terrain->ShortestPath(playerTile, dstTile, monitoredTiles_);
	}

	if (navigationList.empty() && behaviour == FLEE)
	{
		TerrainTile* playerTile = terrain->TileAtMouseCoords(static_cast<int>(pos.x), static_cast<int>(pos.y));
		//get a new path from terrain to get away from enemy
		navigationList = terrain->ClosestUnmonitoredTile(playerTile, monitoredTiles_);

		//is current tile monitored? 
		if (std::find(monitoredTiles_.begin(), monitoredTiles_.end(), playerTile) == monitoredTiles_.end())
		{
			behaviour = SEEK;
		}
	}

	////wait for x seconds
	//if (navigationList.empty() && behaviour == FLEE)
	//{
	//	cout << "behaviour == WAIT" << endl;
	//	behaviour = WAIT;
	//}

	//if (behaviour == WAIT)
	//{
	//	
	//	if (playerWaitTimer > 0.1f)
	//	{			
	//		playerWaitTimer = 0.0f;
	//		cout << "behaviour == SEEK" << endl;
	//		behaviour = SEEK;
	//	}
	//}

	if (!navigationList.empty())
	{
		//if ( behaviour != WAIT )
		//{
			//get the next node and move towards it
			TerrainTile* nextNode = navigationList[navigationList.size() - 1];
			Vector2 nextNodePos = nextNode->Pos();

			//if reached pop it off the top
			if ((pos - nextNode->Pos()).GetMagnitude() < 1.0f)
			{
				pos = nextNode->Pos();
				navigationList.erase(navigationList.end() - 1);
				navigationList.clear();
			}
			else
			{
				int currentTerrainCost = 1;
				if ((pos - nextNode->Pos()).GetMagnitude() < TILE_SIZE * 0.5f)
				{
					currentTerrainCost = nextNode->Cost();
				}

				//TODO FIX - .GetNormal does not work on vector with Magnitude of 0
				Vector2 direction = (nextNodePos - pos).GetNormal();
				Vector2 velocity = (direction * 75) * delta_;
				velocity *= 1.f / (float)currentTerrainCost;
				pos += velocity;

				//rotate animation
				if (direction.x > 0.6) //heading right
				{
					RotateSprite(playerTexture, 0);
				}
				else if (direction.x < -0.6) //heading left
				{
					RotateSprite(playerTexture, PI);
				}
				else if (direction.y > 0.6) //heading down
				{
					RotateSprite(playerTexture, PI / 2);
				}
				else if (direction.y < -0.6) //heading up
				{
					RotateSprite(playerTexture, -(PI / 2));
				}
			}



			//if ( playerWaitTimer > 2.0f )
			//{
			//	navigationList.clear();
			//	playerWaitTimer = 0.0f;
			//}
		//}
	}
	



	//update player rect
	rect.centre = pos;

	//check if bullet collided with player
	for (auto& bullet : bullets_)
	{
		if (Collision::RectCollision(bullet.GetRect(), rect))
		{
			cout << "bullet struck player" << endl;
			return PUS_DIED;
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