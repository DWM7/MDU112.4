#pragma once

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual GameObjectType GetType()
	{
		return egotPlayer;
	}

	virtual void Save(std::ofstream& os);
	virtual void Load(std::ifstream& is);

protected:
	virtual void RenderInternal(Gdiplus::Graphics& canvas);

protected:
	int health;
};

