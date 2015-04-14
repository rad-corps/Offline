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

#define SCREEN_W 1024
#define SCREEN_H 768


int main( int argc, char* argv[] )
{	

	cout << "0: Place Grass Tile" << endl;
	cout << "1: Place Tree Tile" << endl;
	cout << "2: Place Wall Tile" << endl;
	cout << "3: Place Floor Tile" << endl;
	cout << "4: Place Door Tile" << endl;
	cout << "5: Place Water Tile" << endl;
	cout << "P: Place Player" << endl;
	cout << "E: Place Enemy" << endl;
	cout << "Enter: Start Game" << endl;

	srand((unsigned int)time(NULL));
	Initialise(SCREEN_W, SCREEN_H, false, "Offline");
	Terrain terrain(SCREEN_W/16, SCREEN_H/16);
	
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