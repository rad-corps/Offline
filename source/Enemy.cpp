//Enemy.cpp

#include "CONSTS.h"

#include "Enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy(Terrain* terrain_)
{
	terrain = terrain_;
	nextGoalNode = 0;
	animationTimer = 0.0f;
	animSwitch = 0;
	behaviour = EB_PATROL;
}

Enemy::~Enemy()
{}

Vector2 Enemy::Pos()
{
	return pos;
}

//
//void Enemy::SetTexture(SDL_Texture* texture_)
//{
//	enemyTexture = texture_;
//}

void Enemy::Update(float delta_)
{
	animationTimer += delta_;
	if ( animationTimer > 0.6f)
	{
		animationTimer = 0.0f;
		animSwitch++;
	}

	

	if ( behaviour == EB_PATROL )
	{

		//while the navigationList is not empty. 
		if (!navigationList.empty())
		{
			//get the next node and move towards it
			TerrainTile* nextNode = navigationList[navigationList.size() - 1];
			Vector2 nextNodePos = nextNode->Pos();

			//if reached pop it off the top
			if ((pos - nextNode->Pos()).GetMagnitude() < 1.0f)
			{
				pos = nextNode->Pos();
				currentTile = *(navigationList.end() - 1);
				navigationList.erase(navigationList.end() - 1);
			}
			else
			{
				//TODO FIX - .GetNormal does not work on vector with Magnitude of 0
				direction = (nextNodePos - pos).GetNormal();
				Vector2 velocity = (direction * 50) * delta_;
				velocity *= 1.f/(float)currentTile->Cost();
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
			navigationList = terrain->ShortestPath(terrain->TileAtMouseCoords(pos.x, pos.y), goalNodes[nextGoalNode]);
		}
	}//if (behaviour == EB_PATROL)
	else if ( behaviour == EB_PURSUE)
	{
		std::cout << "behaviour == EB_PURSUE" << std::endl;
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
	textures.push_back(CreateSprite("./resources/images/enemyFront.png", TILE_SIZE, TILE_SIZE));
	textures.push_back(CreateSprite("./resources/images/enemyBack.png", TILE_SIZE, TILE_SIZE));
	textures.push_back(CreateSprite("./resources/images/enemySide.png", TILE_SIZE, TILE_SIZE));
	textures.push_back(CreateSprite("./resources/images/armyfront1.png", TILE_SIZE, TILE_SIZE));
	textures.push_back(CreateSprite("./resources/images/armyfront2.png", TILE_SIZE, TILE_SIZE));
	nodeTexture = CreateSprite("./resources/images/node.png", TILE_SIZE, TILE_SIZE);
	viewTexture = CreateSprite("./resources/images/enemyView.png", TILE_SIZE, TILE_SIZE);
	addingNodes = false;
	player = player_;
}
EnemyList::~EnemyList()
{
}

void EnemyList::DrawViewFrustrum(Enemy* enemy_)
{
	TerrainTile* prevTile = terrain->TileAtMouseCoords(enemy_->Pos().x, enemy_->Pos().y);
	TerrainTile* playerTile = terrain->TileAtMouseCoords(player->Pos().x, player->Pos().y);

	for (int dist = 0; dist < 6; ++dist )
	{
		TerrainTile* nextTile = terrain->TileAtDirection(prevTile, enemy_->direction);
		prevTile = nextTile;

		//get the tiles 90deg in either direction
		std::vector<TerrainTile*> fanTiles;
		for (int width = 0; width < dist; ++width)
		{
			TerrainTile* tempTile1 = terrain->TileAtDirection(prevTile, enemy_->direction.Rotate90(true), width + 1);
			TerrainTile* tempTile2 = terrain->TileAtDirection(prevTile, enemy_->direction.Rotate90(false), width + 1);
			fanTiles.push_back(tempTile1);
			fanTiles.push_back(tempTile2);

			if ( tempTile1 == playerTile || tempTile2 == playerTile)
			{
				enemy_->behaviour = EB_PURSUE;
			}
		}

		if ( nextTile != nullptr )
		{
			MoveSprite(viewTexture, nextTile->Pos().x, nextTile->Pos().y);
			DrawSprite(viewTexture);

			for ( auto& terrainTile : fanTiles)
			{
				if ( terrainTile != nullptr)
				{
					MoveSprite(viewTexture, terrainTile->Pos().x, terrainTile->Pos().y);
					DrawSprite(viewTexture);
				}
			}
		}
	}
}

//EnemyList
void
EnemyList::Draw()
{
	//draw the enemies
	for (auto& enemy : enemyList)
	{
		bool flip = false;
		//which way is the enemy heading? 
		SDL_Texture * tempTexture;
		if (enemy.direction.x > 0.6) //heading right
		{
			flip = true;
			tempTexture = textures[2];
		}
		else if (enemy.direction.x < -0.6) //heading left
		{
			tempTexture = textures[2];
		}
		else if (enemy.direction.y > 0.6) //heading down
		{
			if ( enemy.animSwitch % 2 == 0 )
				tempTexture = textures[3];
			else
				tempTexture = textures[4];
		}
		else if (enemy.direction.y < -0.6) //heading up
		{
			tempTexture = textures[1];
		}

		//draw an enemy
		MoveSprite(tempTexture, enemy.Pos().x, enemy.Pos().y);
		DrawSprite(tempTexture, flip);

		//draw the enemies view
		DrawViewFrustrum(&enemy);

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
		enemy.Update(delta_);
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



