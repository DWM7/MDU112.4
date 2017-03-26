#include "stdafx.h"
#include "Saving.h"
#include "GameManager.h"


Saving::Saving(const Vector2i& _location)
{
	location = _location;
}


Saving::~Saving()
{
}

void Saving::Save(std::ofstream & os)
{
	GameObject::Save(os);

	os << save_function << std::endl;
}

void Saving::Load(std::ifstream & is)
{
	GameObject::Load(is);

	is >> save_function;
}

void Saving::RenderInternal(Gdiplus::Graphics & canvas)
{
	GameFrameworkInstance.DrawRectangle(canvas,
		AABBi(Vector2i(-10, -10), Vector2i(10, 10)),
		true, Gdiplus::Color::Yellow);
}

