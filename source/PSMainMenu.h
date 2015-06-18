//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "ProgramState.h"
#include "GLText.h"
#include "DatabaseManager.h"


class PSMainMenu : public ProgramState, public InputListener
{
public:
	PSMainMenu();
	virtual ~PSMainMenu();

	//Program State Interface Requirements
	virtual ProgramState* Update(float delta);
	virtual void Draw();

	//Input Listener Interface Requirements
	virtual void KeyStroke(SDL_Keycode key_);	
	virtual void MouseClick(int mouseButton);//SDL_BUTTON_LEFT 1, SDL_BUTTON_MIDDLE 2, SDL_BUTTON_RIGHT 3
	virtual void MouseDown(int mouseButton);

private:
	void Init();
	GLText startGameText;
	GLText createLevelText;
	ProgramState* newState;

	bool initialised;
};

