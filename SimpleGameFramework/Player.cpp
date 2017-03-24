#include "stdafx.h"
#include "Player.h"
#include "GameManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Save(std::ofstream & os)
{
	GameObject::Save(os);

	os << health << std::endl;
}

void Player::Load(std::ifstream & is)
{
	GameObject::Load(is);

	is >> health;
}

void Player::RenderInternal(Gdiplus::Graphics & canvas)
{
	Vector2i dimensions = GameManagerInstance.GetScreenDimensions();
	Vector2i centrePoint = dimensions * 0.5f;

	// centre the player in the middle of the view
	GameFrameworkInstance.DrawRectangle(canvas,
		AABBi(Vector2i(-10, -10) + centrePoint, 
			  Vector2i(10, 10) + centrePoint),
		true, Gdiplus::Color::Gainsboro);
}
