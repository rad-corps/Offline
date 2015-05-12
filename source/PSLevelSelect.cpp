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
	cout << "1" << endl;
 	testText.SetText("Level Select");
	testText.SetPos(Vector2(100,100));
	testText.SetAlignment(ALIGN_CENTRE);

cout << "2" << endl;

	//get all the levels from the database
	DatabaseManager dm;
	char * error;
cout << "2.5" << endl;
	dm.Select(DB_STR, "tbl_level", "*", "", "", error);

cout << "3" << endl;
	for (int i = 0; i < dm.Rows(); ++i)
	{
		string levelID = ToString(dm.GetValueInt(i, "ID"));
		cout << levelID << endl;
	}
cout << "4" << endl;
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