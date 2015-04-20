//Enemy.cpp

#include "CONSTS.h"

#include "Enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy(Terrain* terrain_)
{
	terrain = terrain_;
	nextGoalNode = 0;
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
			navigationList.erase(navigationList.end() - 1);
		}
		else
		{
			//TODO FIX - .GetNormal does not work on vector with Magnitude of 0
			direction = (nextNodePos - pos).GetNormal();
			Vector2 velocity = (direction * 50) * delta_;
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
EnemyList::EnemyList(Terrain* terrain_)
{
	terrain = terrain_;
	textures.push_back(CreateSprite("./resources/images/enemyFront.png", TILE_SIZE, TILE_SIZE));
	textures.push_back(CreateSprite("./resources/images/enemyBack.png", TILE_SIZE, TILE_SIZE));
	textures.push_back(CreateSprite("./resources/images/enemySide.png", TILE_SIZE, TILE_SIZE));
	nodeTexture = CreateSprite("./resources/images/node.png", TILE_SIZE, TILE_SIZE);
	viewTexture = CreateSprite("./resources/images/enemyView.png", TILE_SIZE, TILE_SIZE);
	addingNodes = false;
}
EnemyList::~EnemyList()
{
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
			tempTexture = textures[0];
		}
		else if (enemy.direction.y < -0.6) //heading up
		{
			tempTexture = textures[1];
		}

		TerrainTile* nextTile = terrain->TileAtDirection(terrain->TileAtMouseCoords(enemy.Pos().x, enemy.Pos().y), enemy.direction);
		MoveSprite(viewTexture, nextTile->Pos().x, nextTile->Pos().y);
		DrawSprite(viewTexture);

		MoveSprite(tempTexture, enemy.Pos().x, enemy.Pos().y);
		DrawSprite(tempTexture, flip);

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



