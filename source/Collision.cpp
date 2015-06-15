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