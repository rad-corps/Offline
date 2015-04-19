#pragma once

#include <SDL2/SDL.h>

class MouseListener
{
public: 
	virtual void LMBClick() = 0;
	//virtual void KeyUp(SDL_Keycode key_) = 0;
};