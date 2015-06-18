//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
/////////////////////////////////////////////////////////////////////////

#include "Goal.h"
#include "CONSTS.h"


Goal::Goal()
{
	goalTexture = CreateSprite("./resources/images/terrain_goal.png", TILE_SIZE, TILE_SIZE);
}


Goal::~Goal()
{
}

Vector2 Goal::Pos()
{
	return pos;
}

void Goal::SetStartingPos(int row_, int col_)
{
	pos.y = row_ * TILE_SIZE;
	pos.x = col_ * TILE_SIZE;
}

void Goal::MouseClick(int mouseButton)
{
	if (mouseButton == 1)
	{
		int mouseX, mouseY;
		GetMouseLocation(mouseX, mouseY);

		pos.x = mouseX;
		pos.y = mouseY;

		pos.x = (int)(pos.x / TILE_SIZE);
		pos.y = (int)(pos.y / TILE_SIZE);

		pos.x *= TILE_SIZE;
		pos.y *= TILE_SIZE;
	}
	
}

void Goal::Draw()
{
	MoveSprite(goalTexture, pos.x, pos.y);
	DrawSprite(goalTexture);
}