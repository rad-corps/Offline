//Enemy.cpp

#include "CONSTS.h"

#include "Enemy.h"
#include <iostream>
#include <cmath> //fabs
#include <algorithm>//std::find

using namespace std;

Enemy::Enemy(Terrain* terrain_)
{
	terrain = terrain_;
	nextGoalNode = 0;
	animationTimer = 0.0f;
	animSwitch = 0;
	behaviour = EB_PATROL;
	currentTile = nullptr;	
	currentTerrainCost = 1;
}

Enemy::~Enemy()
{}

void Enemy::AddGoalNode(TerrainTile* goalNode_)
{
	goalNodes.push_back(goalNode_);
}

std::vector<TerrainTile*> Enemy::GetGoalNodes()
{
	return goalNodes;
}

Vector2 Enemy::Pos()
{
	return pos;
}

//
//void Enemy::SetTexture(SDL_Texture* texture_)
//{
//	enemyTexture = texture_;
//}

void Enemy::Update(float delta_, Player* player_)
{
	animationTimer += delta_;
	if ( animationTimer > 0.6f)
	{
		animationTimer = 0.0f;
		animSwitch++;
	}

	//set all tiles to be not watched by enemy
	for (int row = 0; row < terrain->Rows(); ++row)
	{
		for (int col = 0; col < terrain->Cols(); ++col)
		{
			terrain->TileAt(row, col).watchedByEnemy = false;
		}
	}

	//update viewable tiles
	viewableTiles.clear();
	for (int row = 0; row < terrain->Rows(); ++row)
	{
		for (int col = 0; col < terrain->Cols(); ++col)
		{
			//is tile within viewable distance?????
			//get the tile pos
			Vector2 tilePos = terrain->TileAt(row, col)->Pos();
			Vector2 directionToTile = (tilePos - Pos()).GetNormal();
			float distanceToTile = (tilePos - Pos()).GetMagnitude();
			float angleToTile = fabs(direction.AngleBetweenVectors(directionToTile));

			//compare the distance and angle
			if (distanceToTile < 400.f && angleToTile < 0.65f)
			{
				terrain->TileAt(row, col).watchedByEnemy = true;
				viewableTiles.push_back(terrain->TileAt(row, col));
			}
		}
	}

	//can enemy see player? 
	TerrainTile* playerTile = terrain->TileAtMouseCoords(player_->Pos().x, player_->Pos().y);
	if (std::find(viewableTiles.begin(), viewableTiles.end(), playerTile) == viewableTiles.end())
	{
		behaviour = EB_PATROL;
	}
	else
	{
		behaviour = EB_PURSUE;
	}


	if ( behaviour == EB_PATROL )
	{

		//while the navigationList is not empty. 
		if (!navigationList.empty())
		{
			//get the next node and move towards it
			TerrainTile* nextNode = navigationList[navigationList.size() - 1];
			Vector2 nextNodePos = nextNode->Pos();

			if ((pos - nextNode->Pos()).GetMagnitude() < TILE_SIZE * 0.5f)
			{
				currentTerrainCost = nextNode->Cost();
			}

			//if reached pop it off the top
			if ((pos - nextNode->Pos()).GetMagnitude() < 1.f)
			{
				//pos = nextNode->Pos();
				currentTile = *(navigationList.end() - 1);
				navigationList.erase(navigationList.end() - 1);
				//cout << "next tile: " << currentTile << endl;
			}
			else
			{
				//TODO FIX - .GetNormal does not work on vector with Magnitude of 0
				direction = (nextNodePos - pos).GetNormal();
				Vector2 velocity = (direction * 50) * delta_;
				//velocity *= 1.f/(float)currentTile->Cost();
				velocity *= 1.f / (float)currentTerrainCost;				
				pos += velocity;
			}
		}
		else
		{
			//increment nextGoalNode
			++nextGoalNode;
			if (nextGoalNode == goalNodes.size())
				nextGoalNode = 0;

			//get the navlist
			if ( currentTile == nullptr)
				navigationList = terrain->ShortestPath(terrain->TileAtMouseCoords(pos.x, pos.y), goalNodes[nextGoalNode]);
			else
				navigationList = terrain->ShortestPath(currentTile, goalNodes[nextGoalNode]);
			
		}
	}//if (behaviour == EB_PATROL)
	else if ( behaviour == EB_PURSUE)
	{
		//std::cout << "behaviour == EB_PURSUE" << std::endl;
	}
}

void Enemy::SetPos(int x_, int y_)
{
	pos.x = x_;
	pos.y = y_;
}

void Enemy::AddNode(TerrainTile* tile_)
{
	goalNodes.push_back(tile_);	
}

//EnemyList
EnemyList::EnemyList(Terrain* terrain_, Player * player_)
{
	terrain = terrain_;
	textures.push_back(CreateSprite("./resources/images/enemy1.png", TILE_SIZE, TILE_SIZE));
	textures.push_back(CreateSprite("./resources/images/enemy2.png", TILE_SIZE, TILE_SIZE));
	textures.push_back(CreateSprite("./resources/images/enemy_attack.png", TILE_SIZE, TILE_SIZE));
	nodeTexture = CreateSprite("./resources/images/node.png", TILE_SIZE, TILE_SIZE);
	viewTexture = CreateSprite("./resources/images/enemyView.png", TILE_SIZE, TILE_SIZE);
	currentTileTexture = CreateSprite("./resources/images/current_tile.png", TILE_SIZE, TILE_SIZE);
	addingNodes = false;
	player = player_;
}
EnemyList::~EnemyList()
{
}

void EnemyList::AddEnemy(Enemy enemy_)
{
	enemyList.push_back(enemy_);
}

std::vector<Enemy>
EnemyList::GetEnemyList()
{
	return enemyList;
}

void EnemyList::DrawViewFrustrum(Enemy* enemy_)
{
	//display viewable tiles
	for (auto & viewableTile : enemy_->viewableTiles)
	{
		MoveSprite(viewTexture, viewableTile->Pos().x, viewableTile->Pos().y);
		DrawSprite(viewTexture);
	}
}

//EnemyList
void
EnemyList::Draw()
{
	

	bool flip = false;
	//draw the enemies
	for (auto& enemy : enemyList)
	{
		//draw the enemies view
		DrawViewFrustrum(&enemy);

		SDL_Texture * tempTexture;

		if (enemy.behaviour == EB_PATROL)
		{
			if (enemy.animSwitch % 2 == 0)
			{
				tempTexture = textures[0];
			}
			else
			{
				tempTexture = textures[1];
			}

			//which way is the enemy heading? 
			if (enemy.direction.x > 0.6) //heading right
			{
				RotateSprite(tempTexture, 0);
			}
			else if (enemy.direction.x < -0.6) //heading left
			{
				RotateSprite(tempTexture, PI);
			}
			else if (enemy.direction.y > 0.6) //heading down
			{
				RotateSprite(tempTexture, PI / 2);
			}
			else if (enemy.direction.y < -0.6) //heading up
			{
				RotateSprite(tempTexture, -(PI / 2));
			}
		}
		else if (enemy.behaviour == EB_PURSUE)
		{
			//get the angle to rotate the enemy at			
			tempTexture = textures[2];
			enemy.direction = enemy.Pos() - player->Pos();
			enemy.direction.AddAngle(3.14f);
			RotateSprite(tempTexture, enemy.direction.GetAngle());
		}


		
		

		//draw an enemy
		MoveSprite(tempTexture, enemy.Pos().x, enemy.Pos().y);
		DrawSprite(tempTexture, flip);

		////draw the current tile
		//if (enemy.currentTile != nullptr)
		//{
		//	MoveSprite(currentTileTexture, enemy.currentTile->Pos().x, enemy.currentTile->Pos().y);
		//	DrawSprite(currentTileTexture);
		//}

		

		//draw the nodes
		for (auto& terrainTile : enemy.goalNodes)
		{
			MoveSprite(nodeTexture, terrainTile->Pos().x, terrainTile->Pos().y);
			DrawSprite(nodeTexture);
		}
	}
}

void EnemyList::Update(float delta_)
{	
	addingNodes = false; 

	for (auto& enemy : enemyList)
	{
		enemy.Update(delta_, player);
	}
}

void EnemyList::CreateEnemy(int x_, int y_)
{
 	Enemy temp(terrain);
 	//temp.SetTexture(texture);
 	temp.SetPos(x_, y_);
 	enemyList.push_back(temp);
	enemyList[enemyList.size() - 1].AddNode(terrain->TileAtMouseCoords(x_, y_));
 }

 void EnemyList::UserInputGameSetup()
{

}

 void EnemyList::KeyStroke(SDL_Keycode key_)
 {
	 if (addingNodes)
	 {
		 if (key_ == SDLK_RETURN || key_ == SDLK_RETURN2 || key_ == SDLK_f)
		 {
			 addingNodes = false;
			 cout << "Finished adding nodes" << endl;
		 }
	 }	 
 }
 void EnemyList::MouseClick(int mouseButton)
 {
	if (mouseButton == 1 && !addingNodes)
	{
		int mouseX, mouseY;
		GetMouseLocation(mouseX, mouseY);
		mouseX = mouseX / TILE_SIZE;
		mouseY = mouseY / TILE_SIZE;
		mouseX *= TILE_SIZE;
		mouseY *= TILE_SIZE;		
		CreateEnemy((int)mouseX, (int)mouseY);

		cout << "Enemy Placed at \t x: " << mouseX << "\t y: " << mouseY << endl;
		cout << "Left click to add movement nodes " <<  endl;
		cout << "Press F when done" << endl;
		addingNodes = true;
	}
	else if (mouseButton == 1 && addingNodes)
	{
		//create node at location
		int mouseX, mouseY;
		GetMouseLocation(mouseX, mouseY);

		cout << "node created at" << mouseX << ", " << mouseY << endl;
		enemyList[enemyList.size()-1].AddNode(terrain->TileAtMouseCoords(mouseX, mouseY));
	}
 }



