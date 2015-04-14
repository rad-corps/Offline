#pragma once

#include "GLAHGraphics.h"
#include "Vector.h"
#include "Terrain.h"
#include <vector>

class Player
{
public:
	Player();
	~Player();

	void Update(float delta_);
	void Draw();
	void UserInputGameSetup();
	void UserInput(Terrain* terrain_);

private:
	Vector2 pos;
	SDL_Texture* playerTexture;
	std::vector<TerrainTile*> navigationList;
};

