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
 	testText.SetText("Level Select");
	testText.SetPos(Vector2(100,100));
	testText.SetAlignment(ALIGN_CENTRE);

	//get all the levels from the database
	DatabaseManager dm;
	char * error = nullptr;
	dm.Select(DB_STR, "tbl_level", "*", "", "", error);

	for (int i = 0; i < dm.Rows(); ++i)
	{
		string levelID = ToString(dm.GetValueInt(i, "ID"));
		cout << levelID << endl;
	}
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