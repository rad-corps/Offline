//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// For AIE Advanced Diploma - Game Development Using CPP
//\
/////////////////////////////////////////////////////////////////////////
#include "DatabaseManager.h"
#include <time.h>
#include <iostream>
#include <string>
#include <iostream>
#include "GLAHGraphics.h"
#include "Terrain.h"


using namespace std;

#define INVADERS_FONT "./fonts/feisarv5.fnt"


int main( int argc, char* argv[] )
{	

	srand((unsigned int)time(NULL));
	Initialise(1024,768, false, "Offline");
	Terrain terrain;
	
	AddFont("./fonts/feisarv5.fnt");
	float delta;
	SDL_Texture* playerTexture = CreateSprite("./resources/images/player.png", 16,16);
	do 
	{
		delta = GetDeltaTime();
		MoveSprite(playerTexture, 0, 16);
		DrawSprite(playerTexture);

		terrain.Update(delta);
		terrain.Draw();
	} while ( !FrameworkUpdate() ); 

	return 0;
}