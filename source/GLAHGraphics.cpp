//GLAHGraphics.cpp
//Author: Adam Hulbert
//

#include "CONSTS.h"
#include <stdio.h>

#include "GLAHGraphics.h"
#include <SDL2/SDL_image.h>
//#include "GLAH/GLAHInput.h"
//#include "GLAH/Shaders.h"
#include <iostream>
//glfw include

//#include "GLAH/SOIL.h"
#include <chrono> //std::chrono::time_point
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include <array>

using namespace std::chrono; 

std::map<SDL_Keycode, bool> keyDownList; //key, isDown
std::map<int, bool> msBtnDwn;

	
//contains additional information about sprite rotation, scale, position etc.
std::map<SDL_Texture*, GLAHEntity> spriteList;

std::vector<InputListener*> inputListeners;



//GLFWwindow* window;

//SDL Specific
/////////////////////////////
//Main loop flag
bool quit = false;

//bool lmbDown = false;

//Event handler
SDL_Event e;

//The window we'll be rendering to
SDL_Window* window = NULL;
    
//The surface contained by the window
SDL_Surface* screenSurface = NULL;

SDL_Renderer* renderer;

//GLuint VBO;
//GLuint IBO;

//timers for delta time
std::chrono::time_point<high_resolution_clock> timeBegin;
std::chrono::time_point<high_resolution_clock> timeEnd;

//timers for profiling
std::chrono::time_point<high_resolution_clock> profileBegin;
std::chrono::time_point<high_resolution_clock> profileEnd;

double delta;


SDL_Window*		GetWindow()
{
	return window;
}

void DrawLine(int xOrigin_, int yOrigin_, int xDest_, int yDest_)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, xOrigin_, yOrigin_, xDest_, yDest_);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

//one at a time. 
void AddInputListener(InputListener* listener_)
{
	inputListeners.push_back(listener_);
}

//no bounds checking
void ReplaceInputListener(InputListener* inputListener_, int index_)
{
	inputListeners[index_] = inputListener_;
}

void			NullifyInputListeners()
{
	for (auto & listener : inputListeners)
		listener = nullptr;
}

void			ClearInputListeners()
{
	bool clearListeners = true;

	for ( auto& listener : inputListeners)
	{
		if (listener != nullptr)
		{
			clearListeners = false;
		}
	}

	if (clearListeners)
		inputListeners.clear();
}

//unsigned int	GLAHGraphics::CreateSprite	
// textureName_		: filename/path of the texture to load
// width_			: width of texture
// height_			: height of texture
// parentSpriteID_	: sprite ID of sprite to parent to (0 if no parent)
// originOffset_	: the point of rotation, this is relative to the sprites own space. 
//						Default value is Vector3
// colour_			: not implemented
SDL_Texture* CreateSprite	( const char* textureName_, 
									 int width_, int height_, 
									 SDL_Texture* parentSprite_, 
									 Vector2 childOffsetInfo_, 
									 SColour colour_ )
 {
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( textureName_ );
    //cout << "img w: " << loadedSurface->w << "img h: " << loadedSurface->h << endl;
	//cout << "passed w: " << width_ << "passed h: " << height_ << endl;    
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", textureName_, IMG_GetError() );
		return nullptr;
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", textureName_, SDL_GetError() );
			return nullptr;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

	//Create an entity with position, scale, rotation info
	GLAHEntity glahEntity;
	glahEntity.size.x = loadedSurface->w;
	glahEntity.size.y = loadedSurface->h;
	glahEntity.parentSprite = parentSprite_;
	glahEntity.scaleX = (float)width_ / (float)loadedSurface->w;
	glahEntity.scaleY = (float)height_ / (float)loadedSurface->h;

	//cout << "scalex: " << glahEntity.scaleX << "\t scaley: " << glahEntity.scaleY << endl;
	//glahEntity.spriteID = newTexture;
	//glahEntity.position = Vector3((float)x_, (float)y_, 1.f);
	glahEntity.childOffsetInfo = childOffsetInfo_;

	//add to the spriteList (map) using the texture_handle as the key
	spriteList[newTexture] = glahEntity;
	
	//set the UV's to max incase they are not set by user
	std::array<float, 4> tempArray;
	tempArray[0] = 0;
	tempArray[1] = 0;
	tempArray[2] = glahEntity.size.x;
	tempArray[3] = glahEntity.size.y;
	SetSpriteUVCoordinates(newTexture, tempArray.data());

    return newTexture;
}

void			
ScaleSprite( SDL_Texture* sprite_, float scalarX_, float scalarY_ )
{
	spriteList[sprite_].scaleX = scalarX_;
	spriteList[sprite_].scaleY = scalarY_;
}

void GLAHErroCallback(int errorCode_, const char *errStr_)
{
	cout << "GLFW error: " << errStr_ << endl;
}

void StartTimer()
{
	profileBegin = high_resolution_clock::now();
}

double StopTimer()
{
	profileEnd = high_resolution_clock::now();
	double ret = duration_cast<duration<double> >(profileEnd - profileBegin).count();
	return ret;
}

//Calculate Delta time (time in miliseconds since last update)
void CalculateDelta()
{
	timeEnd = high_resolution_clock::now();
	delta =  duration_cast<duration<double> >(timeEnd - timeBegin).count();
	timeBegin = high_resolution_clock::now();
}

float GetDeltaTime()
{
	return delta;
}

bool FrameworkUpdate()
{
    CalculateDelta();

	//Update screen
    SDL_RenderPresent( renderer );

	//While application is running
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }
		else if ( e.type == SDL_KEYDOWN ) 
		{
			keyDownList[e.key.keysym.sym] = true;
			
			//send to listeners
			for (auto & inputListener : inputListeners)
			{
				if (inputListener != nullptr)
				{
					inputListener->KeyStroke(e.key.keysym.sym);
				}
			}
		}
		else if ( e.type == SDL_KEYUP ) 
		{
			keyDownList[e.key.keysym.sym] = false;
		}
		else if ( e.type == SDL_MOUSEBUTTONDOWN ) 
		{		
			//send off to the listeners if available			
			for (auto & inputListener : inputListeners)
			{
				if (inputListener != nullptr)
				{
					inputListener->MouseClick(e.button.button);
				}
			}

			if ( e.button.button == SDL_BUTTON_LEFT )
			{			
				msBtnDwn[0] = true;
			}
			if ( e.button.button == SDL_BUTTON_RIGHT )
			{
				msBtnDwn[1] = true;
			}
		}
		else if ( e.type == SDL_MOUSEBUTTONUP ) 
		{
			if ( e.button.button == SDL_BUTTON_LEFT )
			{
				msBtnDwn[0] = false;
			}
			if ( e.button.button == SDL_BUTTON_RIGHT )
			{
				msBtnDwn[1] = false;
			}
		}
    }

	//send MouseDown events
	if (msBtnDwn[0] == true)
	{
		for (auto &listener : inputListeners)
		{
			if ( listener != nullptr )
				listener->MouseDown(1);
		}
	}

	if (msBtnDwn[1] == true)
	{
		for (auto &listener : inputListeners)
		{
			if (listener != nullptr)
				listener->MouseDown(3);
		}
	}

	ClearInputListeners();

    //Clear screen
    SDL_RenderClear( renderer );

	return quit;
}

void Shutdown()
{
	//Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();
}

int Initialise(int a_iWidth, int a_iHeight, bool a_bFullscreen, const char* a_pWindowTitle  )
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
	else
    {
        //Create window
        window = SDL_CreateWindow( a_pWindowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, a_iWidth, a_iHeight, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
		else
        {
			//Create renderer for window
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if( renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            }
			else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                }
            }
        }
	}

	//initialise common keys used
	//keyDownList[

	timeBegin = high_resolution_clock::now();

	return 0;
}

//GLAH::DrawSprite ( unsigned int spriteID_)
void DrawSprite(SDL_Texture* sprite_, bool xFlip_, float alpha_, SDL_Point* origin_)
{
	//get information about the sprite
	GLAHEntity entity = spriteList[sprite_];
		
	float xSize = entity.size.x * entity.scaleX;
	float ySize = entity.size.y * entity.scaleY;
	//SDL_Rect src = { 0, 0, static_cast<int>(entity.size.x), static_cast<int>(entity.size.y)};
	SDL_Rect src = { (int)entity.UV[0], (int)entity.UV[1], (int)entity.UV[2], (int)entity.UV[3] };

	SDL_Rect dst = { static_cast<int>(entity.position.x), static_cast<int>(entity.position.y), static_cast<int>(xSize), static_cast<int>(ySize) };

	//flipping horizontally?
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if ( xFlip_ )
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	//SDL_RenderCopyEx( renderer, sprite_, NULL, &dst, entity.rotation * 57.2957795f, origin_, flip );	
	SDL_RenderCopyEx(renderer, sprite_, &src, &dst, entity.rotation * 57.2957795f, origin_, flip);	
}

//GLAH::DrawSprite
//spriteID_		: The ID of the sprite to draw
//x_			: the absolute (world space) x coordinate to draw 
//y_			: the absolute (world space) y coordinate to draw 
void MoveSprite(SDL_Texture* sprite_, float x_, float y_)
{
	spriteList[sprite_].position.x = x_;
	spriteList[sprite_].position.y = y_;
}

//GLAH::DrawSpriteRelative
//spriteID_		: The ID of the sprite to draw
//xMovement_	: The Relative x movement (current x position + xMovement_)
//yMovement_	: The Relative y movement (current y position + yMovement_)
//rotation_		: Amount to rotate sprite by expressed as radians (current rotation + rotation_)
void MoveSpriteRelative(unsigned int spriteID_, float xMovement_, float yMovement_, float rotation_)
{			
	
}

void RotateSpriteRelative(SDL_Texture* sprite_, float rotation_ )
{
	spriteList[sprite_].rotation += rotation_;
}

void RotateSprite(SDL_Texture* sprite_, float rotation_ )
{
	spriteList[sprite_].rotation = rotation_;
}

GLAHEntity GetGLAHEntity(SDL_Texture* sprite_)
{
	return spriteList[sprite_];
}

Vector2			GetGLAHChildCentrePosition	(SDL_Texture* spriteID_)
{
	Vector2 pos(0.0f,0.0f);

	GLAHEntity child = spriteList[spriteID_];

	if ( child.parentSprite != nullptr )
	{
		//get the parents position (currently drawn from top left)
		Vector2 parentPos = spriteList[child.parentSprite].position;
		
		//find xradius and yradius of parent sprite
		float xRadius = (spriteList[child.parentSprite].size.x  * spriteList[child.parentSprite].scaleX) / 2;
		float yRadius = (spriteList[child.parentSprite].size.y  * spriteList[child.parentSprite].scaleY) / 2;

		//find centre of parent sprite TODO this should be stored at time of creation based on position and rotation point
		Vector2 parentCentre = parentPos;
		parentCentre.x += xRadius;
		parentCentre.y -= yRadius;

		//get the angle and the offset from centre
		float child_angle = child.childOffsetInfo.x;
		float child_offset_from_centre = child.childOffsetInfo.y;
		
		//find difference between sprite radius and offset	
		pos.x = child_offset_from_centre * sin(spriteList[child.parentSprite].rotation + child_angle);
		pos.y = child_offset_from_centre * cos(spriteList[child.parentSprite].rotation + child_angle);
		pos += parentCentre;
	}

	return pos;
}

void SetSpriteUVCoordinates	( SDL_Texture* sprite_, float* UVVec4_ )
{
 	for ( int i = 0; i < 4; ++i )
	{
		spriteList[sprite_].UV[i] = UVVec4_[i];
	}
	//cout << "stubbed: SetSpriteUVCoordinates" << endl;
}

void			ClearScreen(){/*cout << "not yet implemented" << endl;*/}	
unsigned int	DuplicateSprite			( unsigned int spriteID_ ){cout << "not yet implemented" << endl; return 0;}
void			DestroySprite			( unsigned int spriteID_ ){cout << "not yet implemented" << endl;}
void			SetSpriteColour			( unsigned int spriteID_, SColour& colour_ ){cout << "not yet implemented" << endl;}
void			GetSpriteColour			( unsigned int spriteID_, SColour& colour_ ){cout << "not yet implemented" << endl;}

void			DrawString( const char* text_, int xPos_, int yPos_, float size_, SColour colour_)
{

}

void			AddFont( char* fontName_)
{

}

void			SetFont( char* fontName_ )
{
	
}

void			RemoveFont( char* fontName_ )
{
	
}


//INPUT HANDLING-------------------------------------------------------
///////////////////////////////////////////////////////////////////////
bool IsKeyDown( SDL_Keycode key_ )
{
	return keyDownList[key_];
}

bool GetMouseButtonDown( int a_iMouseButtonToTest )
{
	return msBtnDwn[a_iMouseButtonToTest];
}

void GetMouseLocation( int& a_iMouseX, int& a_iMouseY )
{
	//int w, h;
	//SDL_GetWindowSize(window, &w, &h);

	SDL_GetMouseState( &a_iMouseX, &a_iMouseY );
	//a_iMouseY =  h - a_iMouseY;
}
//END INPUT HANDLING
///////////////////////////////////////////////////////////////////////