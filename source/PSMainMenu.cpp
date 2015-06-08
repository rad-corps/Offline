#include "PSMainMenu.h"
#include "PSGameController.h"
#include "PSLevelSelect.h"
#include <iostream>
#include "CONSTS.h"

using namespace std;


PSMainMenu::PSMainMenu()
{
	startGameText.SetText("Begin Simulation");
	startGameText.SetPos(Vector2(SCREEN_W/2, 100));
	startGameText.SetAlignment(ALIGN_CENTRE);
	createLevelText.SetText("Create New Level");
	createLevelText.SetPos(Vector2(SCREEN_W/2, 140));
	createLevelText.SetAlignment(ALIGN_CENTRE);
	
	newState = nullptr;
	initialised = false;
}


PSMainMenu::~PSMainMenu()
{
}

void PSMainMenu::Init()
{
	AddInputListener(this);	
	initialised = true;
}


ProgramState* PSMainMenu::Update(float delta)
{
	if (!initialised)
		Init();

	return newState;
}

void PSMainMenu::Draw()
{
	startGameText.Draw();
	createLevelText.Draw();
}

void PSMainMenu::KeyStroke(SDL_Keycode key_)
{
	if (key_ == SDLK_UP)
	{
		cout << "up pressed in menu" << endl;
	}
	if (key_ == SDLK_DOWN)
	{
		cout << "down pressed in menu" << endl;
	}
	if (key_ == SDLK_RETURN || key_ == SDLK_RETURN2)
	{
		cout << "enter pressed in menu" << endl;
	}
}
void PSMainMenu::MouseClick(int mouseButton)
{
	int mouseX, mouseY;
	GetMouseLocation(mouseX, mouseY);

	//did the mouse intersect a button? 
	if (startGameText.Collision(mouseX, mouseY))
	{		
		newState = new PSLevelSelect();
	}
	if (createLevelText.Collision(mouseX, mouseY))
	{
		newState = new PSGameController();
	}
}
void PSMainMenu::MouseDown(int mouseButton)
{
	//cout << "MouseDown" << endl;
}