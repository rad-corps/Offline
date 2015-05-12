#include "PSMainMenu.h"
#include <iostream>

using namespace std;


PSMainMenu::PSMainMenu()
{
	startGameText.SetText("Start Game");
	startGameText.SetPos(Vector2(100,100));
	createLevelText.SetText("Create New Level");
	createLevelText.SetPos(Vector2(100, 200));

	AddInputListener(this);
}


PSMainMenu::~PSMainMenu()
{
}


ProgramState* PSMainMenu::Update(float delta)
{
	return nullptr;
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
void PSMainMenu::MouseClick(int mouseButton){}
void PSMainMenu::MouseDown(int mouseButton){}