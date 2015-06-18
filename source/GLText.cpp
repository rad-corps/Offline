//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
/////////////////////////////////////////////////////////////////////////

#include "GLAHGraphics.h"
#include "GLText.h"
#include "UVTranslator.h"
#include <locale> //toupper

using namespace std;

GLText::GLText(){
	alignment = TEXT_ALIGNMENT::ALIGN_CENTRE;
	fontTexture = CreateSprite("./resources/images/courier.png", 16, 16);
}
GLText::~GLText(void){}
void GLText::Update(float delta_){}

void GLText::SetPos(Vector2 pos_)
{
	pos = pos_;
	
}

bool GLText::Collision(int x_, int y_)
{
	if (collider.Right() < x_
		|| x_ < collider.Left()
		|| collider.Bottom() > y_
		|| collider.Top() < y_)
		return false;
	return true;
}

void GLText::SetAlignment(TEXT_ALIGNMENT alignment_)
{
	alignment = alignment_;
	if (alignment_ != ALIGN_CENTRE)
	{
		cout << "GLText::SetAlignment: Only ALIGN_CENTRE is supported" << endl;
	}
}

void GLText::SetData(std::string text_)
{
	data = text_;
}

std::string GLText::GetText()
{
	return text;
}

std::string GLText::GetData()
{
	return data;
}



void GLText::SetText(string text_)
{
	text = text_;
	uvs.clear();
	UVTranslator trans(1024,1024,64,64);

	for ( int ch : text_ )
	{
		//get the ascii representation of the character
		ch = (int)toupper(ch);

		ch -= 32; //sprite chart starts from ascii 32
		ch -= 5;  //accidentally missed 5 chars when creating sheet
		
		//create an array to pushback into UVS
		std::array<float, 4> tempArray;

		//determine column and row
		int row = ch / 16;
		int col = ch % 16;

		//dump the uv data into the std::array
		trans.GetUV(tempArray.data(), row, col);

		//uvs is a std::vector<std::array<float, 4>> uvs;
		uvs.push_back(tempArray);
	}
}

void GLText::Draw()
{
	//bail if no text
	if (text.length() < 1)
		return;

	//for each std::array in uvs

	if ( alignment == TEXT_ALIGNMENT::ALIGN_LEFT )
	{
		for ( int i = 0; i < uvs.size(); ++i )
		{
			SetSpriteUVCoordinates(fontTexture, uvs[i].data());
			MoveSprite(fontTexture, pos.x + 16 * i, pos.y); //hardcoded 8 as a step for now, variable size can come later
			DrawSprite(fontTexture);
		}
	}
	
	if ( alignment == TEXT_ALIGNMENT::ALIGN_CENTRE )
	{
		Vector2 colliderCentre = pos;
		colliderCentre.y += 8;
		colliderCentre.x += 8;
		collider = Rect(colliderCentre, (uvs.size() * 16) + 16, 16 + 16);
		DrawLine(collider.Left(), collider.Top(), collider.Right(), collider.Top());
		DrawLine(collider.Left(), collider.Top(), collider.Left(), collider.Bottom());
		DrawLine(collider.Left(), collider.Bottom(), collider.Right(), collider.Bottom());
		DrawLine(collider.Right(), collider.Bottom(), collider.Right(), collider.Top());
		//use a float to find the middle character because it can be halfway for even numbers
		float middle_char = (uvs.size() - 1) / 2.f;
		for ( int i = 0; i < uvs.size(); ++i )
		{
			float charOffset = (i - middle_char) * 16;
			SetSpriteUVCoordinates(fontTexture, uvs[i].data());
			MoveSprite(fontTexture, pos.x + charOffset, pos.y);
			DrawSprite(fontTexture);
		}
	}

	if ( alignment == TEXT_ALIGNMENT::ALIGN_RIGHT)
	{
		//use a float to find the middle character because it can be halfway for even numbers		
		for ( int i = 0; i < uvs.size(); ++i )
		{
			SetSpriteUVCoordinates(fontTexture, uvs[uvs.size() - 1 - i].data());
			MoveSprite(fontTexture, pos.x - 16 * i, pos.y);
			DrawSprite(fontTexture);
		}
	}
}