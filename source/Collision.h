//////////////////////////////////////////////////////////////////////////
// Game Code By Adam Hulbert
// 22/12/2014
// Collision.h
/////////////////////////////////////////////////////////////////////////

#pragma once

//#include "GameObject.h"
#include "Rect.h"

class Collision
{
public:
	~Collision(void);

	//static bool CheckCollision(GameObject* obj1_, GameObject* obj2_);
	static bool RectCollision(Rect r1_, Rect r2_);

private:
	Collision(void);

};