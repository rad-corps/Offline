#pragma once

#include "GLAHGraphics.h"
#include "Vector.h"

class Goal : public InputListener
{
public:
	Goal();
	~Goal();

	//InputListener interface requirement
	virtual void KeyStroke(SDL_Keycode key_){}
	virtual void MouseClick(int mouseButton);
	virtual void MouseDown(int mouseButton){}

	void SetStartingPos(int row_, int col_);

	void Update(float delta_);
	void Draw();

	Vector2 Pos();

private:
	Vector2 pos;
	SDL_Texture* goalTexture;
};

