#pragma once
#include "GameObject.h"
#include "GameManager.h"
class Saving :
	public GameObject
{
public:
	Saving(const Vector2i& _location = Vector2i::Zero);
	virtual ~Saving();

	virtual GameObjectType GetType()
	{
		return egotSaving;
	}

	virtual void Save(std::ofstream& os);
	virtual void Load(std::ifstream& is);

protected:
	virtual void RenderInternal(Gdiplus::Graphics& canvas);

protected:
	int save_function;
};

