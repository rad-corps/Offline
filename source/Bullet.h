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