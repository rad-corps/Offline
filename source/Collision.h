//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
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