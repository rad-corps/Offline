//PSLevelSelect.cpp

#include "PSLevelSelect.h"
#include "Vector.h"

PSLevelSelect::PSLevelSelect()
{
	testText.SetText("Level Select");
	testText.SetPos(Vector2(100,100));
	testText.SetAlignment(ALIGN_CENTRE);

}

PSLevelSelect::~PSLevelSelect()
{}

ProgramState*
PSLevelSelect::Update(float delta_)
{
	return nullptr;
}

void
PSLevelSelect::Draw()
{
	testText.Draw();
} 