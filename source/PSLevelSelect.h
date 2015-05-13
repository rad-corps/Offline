//PSLevelSelect.h

#pragma once

#include "ProgramState.h"
#include "GLText.h"
#include <vector>

class PSLevelSelect : public ProgramState, public InputListener
{
public:

	PSLevelSelect();
	virtual ~PSLevelSelect();

	virtual ProgramState* Update(float delta_);
	virtual void Draw();

		//Input Listener Interface Requirements
	virtual void KeyStroke(SDL_Keycode key_);	
	virtual void MouseClick(int mouseButton);//SDL_BUTTON_LEFT 1, SDL_BUTTON_MIDDLE 2, SDL_BUTTON_RIGHT 3
	virtual void MouseDown(int mouseButton);

private:
	GLText testText;
	std::vector<GLText> levelText;
	bool initialised;

};