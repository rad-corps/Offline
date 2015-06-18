//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
/////////////////////////////////////////////////////////////////////////

#include "GLAHGraphics.h"
//#include "PSGameController.h"
#include "SetupGame.h"
#include <time.h>
#include <cstdlib>
#include "OuterLoop.h"

int main( int argc, char* argv[] )
{	


	OuterLoop outerLoop;
	outerLoop.Go();

	return 0;


	////randomize seed
	//srand((unsigned int)time(NULL));

	//Terrain* terrain = nullptr;
	//Player* player = nullptr;
	//EnemyList* enemyList = nullptr;
	//GameController* gc;

	////load level
	//if (argc > 1)
	//{
	//	int levelID = atoi(argv[1]);
	//	SetupGame::LoadGameObjects(levelID, terrain, player, enemyList);
	//	gc = new GameController(player, terrain, enemyList);
	//}
	//else //straight to create level
	//{
	//	gc = new GameController();
	//}

	////GameController gc;
	//gc->Run();


	//return 0;
}