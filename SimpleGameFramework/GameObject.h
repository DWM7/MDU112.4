#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>

enum GameObjectType
{
	egotBase,
	egotPlayer,
	egotSaving
};

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual GameObjectType GetType()
	{
		return egotBase;
	}

	virtual void Render(Gdiplus::Graphics& canvas);

	static std::list<GameObject*> LoadObjects(std::ifstream& is);
	static void SaveObjects(std::ofstream& os, std::list<GameObject*>& objects);

	virtual void Save(std::ofstream& os);
	virtual void Load(std::ifstream& is);

protected:
	virtual void RenderInternal(Gdiplus::Graphics& canvas) = 0;

public:
	std::string name;
	Vector2i location;
	float rotation = 0;
};

