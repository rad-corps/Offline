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

Vector2 Enemy::Pos()
{
	return pos;
}

void Enemy::SetPos(int x_, int y_)
{
	pos.x = x_;
	pos.y = y_;
}



//EnemyList

EnemyList::EnemyList()
{
	texture = CreateSprite("./resources/images/enemy.png", 16, 16);
}
EnemyList::~EnemyList()
{
}

void EnemyList::Draw()
{
	for (auto &enemy : enemyList)
	{
		MoveSprite(texture, enemy.Pos().x, enemy.Pos().y);
		DrawSprite(texture);
	}
}

void EnemyList::Update(float delta_)
{
	//TODO implement
}

void EnemyList::CreateEnemy(int x_, int y_)
{
 	Enemy temp;
 	temp.SetTexture(texture);
 	temp.SetPos(x_, y_);

 	//TODO check if an enemy already exists at this position

 	enemyList.push_back(temp);
}

void EnemyList::UserInput()
{
	int mouseX, mouseY;
	GetMouseLocation(mouseX, mouseY);
	bool createEnemy = true;
	
	//check for mouse left click (src)
	if (GetMouseButtonDown(0))
	{
		mouseX = (int)(mouseX / 16);
		mouseY = (int)(mouseY / 16);

		mouseX *= 16;
		mouseY *= 16;

		Vector2 pos(mouseX, mouseY);

		//check if enemy exists at this location
		for (auto & enemy : enemyList)
		{
			if (enemy.Pos() == pos)
			{
				createEnemy = false;
			}
		}
		if (createEnemy)
		{
			CreateEnemy((int)pos.x, (int)pos.y);
		}
	}

}