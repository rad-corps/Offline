//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "ProgramState.h"

class OuterLoop
{
public:
	OuterLoop(void);
	~OuterLoop(void);

	//the main game loop, returns when it is time to shut down
	void Go();


private:
	//The state machine variable
	ProgramState* currentProgramState;

	//unsigned int cursorSprite;
	//double mouseX;
	//double mouseY;

	////PROGRAM_STATES new
	//bool shuttingDown;

	float gameTimer;

	const float updateInterval;

};

