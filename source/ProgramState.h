//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
/////////////////////////////////////////////////////////////////////////

#pragma once
class ProgramState
{
public:
	virtual ~ProgramState(){};
	virtual ProgramState* Update(float delta_) = 0;
	virtual void Draw() = 0;

protected:
};

