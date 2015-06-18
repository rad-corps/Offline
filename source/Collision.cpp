//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
/////////////////////////////////////////////////////////////////////////

#include "Collision.h"


Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::RectCollision(Rect platform_, Rect player_)
{
	//platform_.Scale(0.95f);
	//player_.Scale(0.95f);

	if (platform_.Right() < player_.Left()
		|| player_.Right() < platform_.Left()
		|| platform_.Bottom() > player_.Top()
		|| platform_.Top() < player_.Bottom())

		return false;
	return true;
}