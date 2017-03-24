#include "stdafx.h"
#include "GameObject.h"
#include "Saving.h"
#include "Player.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Render(Gdiplus::Graphics & canvas)
{
	// Save the current transformation of the scene
	Gdiplus::Matrix transform;
	canvas.GetTransform(&transform);

	canvas.TranslateTransform((Gdiplus::REAL)location.X,
		(Gdiplus::REAL)location.Y);
	canvas.RotateTransform(rotation);

	RenderInternal(canvas);

	// Restore the transformation of the scene
	canvas.SetTransform(&transform);
}

std::list<GameObject*> GameObject::LoadObjects(std::ifstream & is)
{
	std::list<GameObject*> loadedObjects;

	int numObjects;
	is >> numObjects;

	for (int index = 0; index < numObjects; ++index)
	{
		int dummyInt;
		is >> dummyInt;

		GameObjectType objectType = static_cast<GameObjectType>(dummyInt);

		GameObject* objectPtr = nullptr;
		if (objectType == egotSaving)
		{
			objectPtr = new Saving();
		}
		else if (objectType == egotPlayer)
		{
			objectPtr = new Player();
		}

		// did we create something
		if (objectPtr)
		{
			objectPtr->Load(is);
			loadedObjects.push_back(objectPtr);
		}
	}

	return loadedObjects;
}

void GameObject::SaveObjects(std::ofstream & os, std::list<GameObject*>& objects)
{
	// output the number of objects
	os << objects.size() << std::endl;

	// save all of the objects
	for (GameObject* objectPtr : objects)
	{
		objectPtr->Save(os);
	}
}

void GameObject::Save(std::ofstream & os)
{
	os << (int) GetType() << std::endl;

	os << name << "," << location.X << "," << location.Y << "," << rotation << std::endl;
}

void GameObject::Load(std::ifstream & is)
{
	char dummyChar;

	std::getline(is, name, ',');

	is >> location.X;
	is >> dummyChar;

	is >> location.Y;
	is >> dummyChar;

	is >> rotation;
}
