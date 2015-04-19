//Enemy.cpp

#include "CONSTS.h"

#include "Enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{}

Vector2 Enemy::Pos()
{
	return pos;
}


void Enemy::SetTexture(SDL_Texture* texture_)
{
	enemyTexture = texture_;
}

void Enemy::Update(float delta_)
{
	//while the navigationList is not empty. 
	if (path.empty())
		return;

	if (!path.empty())
	{
		TerrainTile* nodePtr = (*nextNode);
		//if reached pop it off the top
		if ((pos - nodePtr->Pos()).GetMagnitude() < 1.0f)
		{
			++nextNode;
			if (nextNode == path.end())
				nextNode = path.begin();
		}
		else
		{
			//TODO FIX - .GetNormal does not work on vector with Magnitude of 0
			Vector2 direction = (nodePtr->Pos() - pos).GetNormal();
			Vector2 velocity = (direction * 50) * delta_;
			pos += velocity;
		}
	}
}

void Enemy::SetPos(int x_, int y_)
{
	pos.x = x_;
	pos.y = y_;
}

void Enemy::AddNode(TerrainTile* tile_)
{
	path.push_back(tile_);
	nextNode = path.begin();
}


//EnemyList
EnemyList::EnemyList(Terrain* terrain_)
{
	terrain = terrain_;
	texture = CreateSprite("./resources/images/enemy.png", TILE_SIZE, TILE_SIZE);
	addingNodes = false;
}
EnemyList::~EnemyList()
{
}

//EnemyList
void
EnemyList::Draw()
{
	for (auto& enemy : enemyList)
	{
		MoveSprite(texture, enemy.Pos().x, enemy.Pos().y);
		DrawSprite(texture);	
	}
}


void EnemyList::Update(float delta_)
{
	for (auto& enemy : enemyList)
	{
		enemy.Update(delta_);
	}
}

void EnemyList::CreateEnemy(int x_, int y_)
{
 	Enemy temp;
 	temp.SetTexture(texture);
 	temp.SetPos(x_, y_);
 	enemyList.push_back(temp);
 }

 void EnemyList::UserInputGameSetup()
{

}

 void EnemyList::KeyStroke(SDL_Keycode key_)
 {
	 if (key_ == SDLK_f && addingNodes)
	 {
		 addingNodes = false;
		 cout << "Finished adding nodes" << endl;
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



