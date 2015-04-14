#pragma once

#include "GLAHGraphics.h"
#include "Vector.h"

class Player
{
public:
	Player();
	~Player();

	void Update(float delta_);
	void Draw();
	void UserInputGameSetup();
	void UserInput();

private:
	Vector2 pos;
	SDL_Texture* playerTexture;
};

