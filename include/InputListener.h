#pragma once

#include <SDL2/SDL.h>

class InputListener
{
public: 
	virtual void KeyStroke(SDL_Keycode key_) = 0;
	
	//#define SDL_BUTTON_LEFT     1
	//#define SDL_BUTTON_MIDDLE   2
	//#define SDL_BUTTON_RIGHT    3
	virtual void MouseClick(int mouseButton) = 0;
	virtual void MouseDown(int mouseButton) = 0;
};