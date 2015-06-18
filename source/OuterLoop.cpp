//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
/////////////////////////////////////////////////////////////////////////

#include "OuterLoop.h"
#include "GLAHGraphics.h"
#include "ProgramState.h"
#include "PSGameController.h"
#include "GLAHGraphics.h"
#include "PSMainMenu.h"
#include <iostream>
#include "CONSTS.h"

using namespace std;

OuterLoop::OuterLoop(void)
: updateInterval(0.0166666666666666667f)
{
	Initialise(SCREEN_W, SCREEN_H, false, "Offline");

	//cout << "OuterLoop()" << endl;

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
			
			StartTimer();
			newState = currentProgramState->Update(updateInterval);
			double time = StopTimer();
			//cout << "Update took: " << time << endl;
		}
		else
		{
		}

		//change state if required
		if (newState != nullptr)
		{
			NullifyInputListeners();
			delete currentProgramState;
			currentProgramState = newState;
		}

		currentProgramState->Draw();

	} while (FrameworkUpdate() == false);
}
