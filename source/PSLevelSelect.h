//PSLevelSelect.h

#pragma once

#include "ProgramState.h"
#include "GLText.h"

class PSLevelSelect : public ProgramState
{
public:

	PSLevelSelect();
	virtual ~PSLevelSelect();

	virtual ProgramState* Update(float delta_);
	virtual void Draw();

private:
	GLText testText;
};