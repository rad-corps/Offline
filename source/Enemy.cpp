//Enemy.cpp

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

void Enemy::SetPos(int x_, int y_)
{
	pos.x = x_;
	pos.y = y_;
}

EnemyList::EnemyList()
{
	texture = CreateSprite("./resources/images/enemy.png", 16, 16);
}

EnemyList::~EnemyList()
{
	//texture = CreateSprite("./resources/images/enemy.png", 16, 16);
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

void
EnemyList::Update(float delta_)
{
	//
}



 void EnemyList::CreateEnemy(int x_, int y_)
 {
 	Enemy temp;
 	temp.SetTexture(texture);
 	temp.SetPos(x_, y_);

 	//TODO check if an enemy already exists at this position

 	enemyList.push_back(temp);
 }

 void EnemyList::UserInputGameSetup()
{
	int mouseX, mouseY;
	GetMouseLocation(mouseX, mouseY);

	//check for mouse left click (src)
	if (GetMouseButtonDown(0))
	{
		mouseX = mouseX / 16;
		mouseY = mouseY / 16;
		mouseX *= 16;
		mouseY *= 16;
		cout << "Create Enemy \t x: " << mouseX << "\t y: " << mouseY << endl;
		CreateEnemy((int)mouseX, (int)mouseY);
	}


}
