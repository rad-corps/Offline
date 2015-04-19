#pragma once

#include "GLAHGraphics.h"
#include "Vector.h"
#include "Terrain.h"
#include <vector>
#include "InputListener.h"

class Player : public InputListener
{
public:
	Player(Terrain* terrain_);
	~Player();

	void Update(float delta_);
	void Draw();
	void UserInputGameSetup();
	void UserInput(Terrain* terrain_);
	void SetPlaying(bool playing_);

	//InputListener interface requirement
	virtual void KeyStroke(SDL_Keycode key_);
	virtual void MouseClick(int mouseButton);

private:
	Vector2 pos;
	SDL_Texture* playerTexture;
	std::vector<TerrainTile*> navigationList;
	Terrain* terrain;
	bool playing;
};

