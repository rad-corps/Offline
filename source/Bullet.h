//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
/////////////////////////////////////////////////////////////////////////

//Bullet.h

#pragma once

#include "Vector.h"
#include "GLAHGraphics.h"
#include "Rect.h"

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Update(float delta_);
	void Draw();
	bool Active();

	void Shoot(Vector2 pos_, Vector2 dir_);

	Rect GetRect();

private:

	Rect rect;
	Vector2 pos;
	Vector2 magnitude;
	SDL_Texture* bulletTexture;
	bool active;
	float timeActive;
};