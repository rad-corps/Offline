//Enemy.cpp

#include "Enemy.h"

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{}

void Enemy::UserInputGameSetup()
{
	int mouseX, mouseY;
	GetMouseLocation(mouseX, mouseY);

	//check for mouse left click (src)
	if (GetMouseButtonDown(0))
	{
		pos.x = mouseX;
		pos.y = mouseY;

		pos.x = (int)(pos.x / 16);
		pos.y = (int)(pos.y / 16);

		pos.x *= 16;
		pos.y *= 16;
	}
}

void Enemy::SetTexture(SDL_Texture* texture_)
{
	enemyTexture = texture_;
}

//EnemyList

EnemyList::EnemyList()
{
	texture = CreateSprite("./resources/images/enemy.png", 16, 16);
}

 void EnemyList::Create(int x_, int y_)
 {
 	Enemy temp;
 	temp.SetTexture(texture);
 	temp.SetPos(x_, y_);

 	//TODO check if an enemy already exists at this position

 	enemyList.push_back(temp);
 }



private:
	std::vector<Enemy> 
};