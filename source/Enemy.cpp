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

<<<<<<< HEAD
=======
Vector2 Enemy::Pos()
{
	return pos;
}

>>>>>>> 5ce43c405e22c686ade0caf39ec69aa25acc0fca
void Enemy::SetPos(int x_, int y_)
{
	pos.x = x_;
	pos.y = y_;
}
<<<<<<< HEAD
=======



//EnemyList
>>>>>>> 5ce43c405e22c686ade0caf39ec69aa25acc0fca

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

<<<<<<< HEAD
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

void 
EnemyList::LMBClick()
{
	cout << "Enemy::LMBClick();" << endl;
}

 void EnemyList::CreateEnemy(int x_, int y_)
 {
=======
void EnemyList::Update(float delta_)
{
	//TODO implement
}

void EnemyList::CreateEnemy(int x_, int y_)
{
>>>>>>> 5ce43c405e22c686ade0caf39ec69aa25acc0fca
 	Enemy temp;
 	temp.SetTexture(texture);
 	temp.SetPos(x_, y_);

 	//TODO check if an enemy already exists at this position

 	enemyList.push_back(temp);
<<<<<<< HEAD
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
=======
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
>>>>>>> 5ce43c405e22c686ade0caf39ec69aa25acc0fca
