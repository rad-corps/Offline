//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
/////////////////////////////////////////////////////////////////////////

//BulletListener.h
#pragma once

#include "Vector.h"

class BulletListener
{
	public:
		virtual void ShootBullet(Vector2 pos_, Vector2 dir_) = 0;

};