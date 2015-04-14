#include "Player.h"



Player::Player()
{
	playerTexture = CreateSprite("./resources/images/player.png", 16, 16);
}


Player::~Player()
{
}


void Player::UserInputGameSetup()
{
	int mouseX, mouseY;
	GetMouseLocation(mouseX, mouseY);

	//check for mouse left click (src)
	if (GetMouseButtonDown(0))
	{
		pos.x = mouseX;
		pos.y = mouseY;

		pos.x = (int)(pos.x / 16);
		pos.y = (int)(pos.y / 16);;

		pos.x *= 16;
		pos.y *= 16;

	}
}

void Player::Draw()
{
	MoveSprite(playerTexture, pos.x, pos.y);
	DrawSprite(playerTexture);
}

void Player::Update(float delta_)
{

}