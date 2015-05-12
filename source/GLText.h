#pragma once

//#include "GameObject.h"
//#include "../spritesheet/SpriteSheet.h"
#include "GLAHGraphics.h"
#include <string>
#include <vector>
#include <array>
#include "Vector.h"
#include "Rect.h"

enum TEXT_ALIGNMENT
{
	ALIGN_LEFT,
	ALIGN_CENTRE,
	ALIGN_RIGHT
};

class GLText
{
public:
	GLText();
	~GLText(void);

	virtual void Update(float delta_);
	virtual void Draw();

	void SetAlignment(TEXT_ALIGNMENT alignment_);
	void SetText(std::string text_);
	std::string GetText();
	void SetPos(Vector2 pos_);

	//only supported with Centre alignment
	bool Collision(int x_, int y_);

private:
	std::vector<std::array<float, 4>> uvs;
	TEXT_ALIGNMENT alignment;
	std::string text;
	Vector2 pos;
	SDL_Texture* fontTexture;
	Rect collider;
};

