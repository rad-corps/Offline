//////////////////////////////////////////////////////////////////////////
// Offline
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 12/05/2015
// OuterLoop.cpp
/////////////////////////////////////////////////////////////////////////

#include "OuterLoop.h"
#include "GLAHGraphics.h"
#include "ProgramState.h"
#include "PSGameController.h"
#include "PSMainMenu.h"
#include <iostream>
#include "CONSTS.h"

using namespace std;

OuterLoop::OuterLoop(void)
: updateInterval(0.0166666666666666667f)
{
	Initialise(SCREEN_W, SCREEN_H, false, "Offline");

	cout << "OuterLoop()" << endl;

	//mouseX = 0.0;
	//mouseY = 0.0;
	gameTimer = 0.0f;

	//shuttingDown = false;

	currentProgramState = new PSMainMenu();
}


OuterLoop::~OuterLoop(void)
{
	cout << "~OuterLoop()" << endl;
}

void OuterLoop::Go()
{

	do
	{
		//if this is set to something other than null, we switch states. 
		ProgramState* newState = nullptr;

		//update only if we have reached an updateInterval
		gameTimer += GetDeltaTime();
		if (gameTimer > updateInterval)
		{
			gameTimer -= updateInterval;
			newState = currentProgramState->Update(updateInterval);
		}

		//change state if required
		if (newState != nullptr)
		{
			delete currentProgramState;
			currentProgramState = newState;
		}

		currentProgramState->Draw();

	} while (FrameworkUpdate() == false);
}
