//BulletListener.h
#pragma once

#include "Vector.h"

class BulletListener
{
	public:
		virtual void ShootBullet(Vector2 pos_, Vector2 dir_) = 0;

};