//////////////////////////////////////////////////////////////////////////
// Offline
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 12/05/2015
// OuterLoop.h
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

