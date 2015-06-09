//Bullet.cpp

#include "Bullet.h"
#include "CONSTS.h"
#include <iostream>

using namespace std;

Bullet::Bullet()
{
	//create texture
	bulletTexture = CreateSprite("./resources/images/bullet.png", BULLET_SIZE, BULLET_SIZE);
	active = false;
	timeActive = 0.0f;
}

Bullet::~Bullet()
{
//destory texture

}

bool Bullet::Active()
{
	return active;
}

void Bullet::Update(float delta_)
{
	//do not update if inactive
	if (!active)
		return;

	//move bullet through space
	pos += magnitude * delta_;

	//check how long bullet has been active for
	timeActive += delta_;
	if ( timeActive > 3.0f )
		active = false;
}

void Bullet::Draw()
{
	//do not draw if inactive
	if (!active)
		return;

	MoveSprite(bulletTexture, pos.x, pos.y);
	DrawSprite(bulletTexture);
}

void Bullet::Shoot(Vector2 pos_, Vector2 dir_)
{
	cout << "Bullet::Shoot" << endl;

	active = true;
	pos = pos_;
	magnitude = dir_ * 1000;
}