//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// For AIE Advanced Diploma - Game Development Using CPP
//\
/////////////////////////////////////////////////////////////////////////
#include "GLAHGraphics.h"
#include "GameController.h"
#include "SetupGame.h"
#include <time.h>
#include <cstdlib>

void RunTests()
{
	//SetupGame::DBTest1();
	SetupGame::SaveLevel(nullptr, nullptr, nullptr);
}

int main( int argc, char* argv[] )
{	

	////TESTING
	//RunTests();
	//system("pause");
	//return 0;
	////END TESTING

	Initialise(SCREEN_W, SCREEN_H, false, "Offline");
	AddFont("./fonts/feisarv5.fnt");
	//randomize seed
	srand((unsigned int)time(NULL));

	Terrain* terrain = nullptr;
	Player* player = nullptr;
	EnemyList* enemyList = nullptr;
	GameController* gc;

	//load level
	if (argc > 1)
	{
		int levelID = atoi(argv[1]);
		SetupGame::LoadGameObjects(levelID, terrain, player, enemyList);
		gc = new GameController(player, terrain, enemyList);
	}
	else //straight to create level
	{
		gc = new GameController();
	}

	//GameController gc;
	gc->Run();


	return 0;
}