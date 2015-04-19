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


//EnemyList
EnemyList::EnemyList()
{
	texture = CreateSprite("./resources/images/enemy.png", 16, 16);
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
	//TODO implement
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
 
 }
 void EnemyList::MouseClick(int mouseButton)
 {
	if (mouseButton == 1)
	{
		int mouseX, mouseY;
		GetMouseLocation(mouseX, mouseY);

		mouseX = mouseX / 16;
		mouseY = mouseY / 16;
		mouseX *= 16;
		mouseY *= 16;
		cout << "Create Enemy \t x: " << mouseX << "\t y: " << mouseY << endl;
		CreateEnemy((int)mouseX, (int)mouseY);
	}
 }



