//PSLevelSelect.cpp

#include "PSLevelSelect.h"
#include "Vector.h"
#include "DatabaseManager.h"
#include "CONSTS.h"
#include <string>
#include "FrameworkHelpers.h"

using namespace std;

PSLevelSelect::PSLevelSelect()
{
	initialised = false;
 // 	testText.SetText("Level Select");
	// testText.SetPos(Vector2(100,100));
	// testText.SetAlignment(ALIGN_CENTRE);

	//get all the levels from the database
	DatabaseManager dm;
	char * error = nullptr;
	dm.Select(DB_STR, "tbl_level", "*", "", "", error);

	int yPos = 50;

	for (int i = 0; i < dm.Rows(); ++i)
	{
		GLText tempText;
		tempText.SetPos(Vector2(SCREEN_W/2, yPos));
		yPos += 50;
		tempText.SetText(dm.GetValueString(i, "ID"));
		levelText.push_back(tempText);
	}

}

PSLevelSelect::~PSLevelSelect()
{}

ProgramState*
PSLevelSelect::Update(float delta_)
{
	if (!initialised)
	{
		AddInputListener(this);
		initialised = true;
	}

	return nullptr;
}

void
PSLevelSelect::Draw()
{
	for (auto& text : levelText)
	{
		text.Draw();
	}
	//testText.Draw();
} 

void PSLevelSelect::KeyStroke(SDL_Keycode key_)	
{}
void PSLevelSelect::MouseClick(int mouseButton)//SDL_BUTTON_LEFT 1, SDL_BUTTON_MIDDLE 2, SDL_BUTTON_RIGHT 3
{
	cout << "MouseClick" << endl;
	int mouseX, mouseY;
	GetMouseLocation(mouseX, mouseY);

	for (GLText& text : levelText)
	{
		if ( text.Collision(mouseX, mouseY) )
		{
			cout << "Clicked: " << text.GetText() << endl;
		}
	}
}
void PSLevelSelect::MouseDown(int mouseButton)
{}