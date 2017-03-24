#include "stdafx.h"
#include "GameManager.h"
#include "Saving.h"

GameManager& GameManager::Instance()
{
	static GameManager instance;

	return instance;
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

const char* Image1 = "Image1";

void GameManager::BeginPlay()
{
	// Load the image file Untitled.png from the Images folder. Give it the unique name of Image1
	GameFrameworkInstance.LoadImageResource(AppConfigInstance.GetResourcePath("Images/Untitled.png"), Image1);

	screenDimensions.X = AppConfigInstance.GetConfig<int>("Width");
	screenDimensions.Y = AppConfigInstance.GetConfig<int>("Height");

	gameObjects.push_back(new Saving(Vector2i(300, 300)));
	gameObjects.push_back(new Saving(Vector2i(100, 100)));
	gameObjects.push_back(new Player());

	playerPtr = dynamic_cast<Player*>(gameObjects.back());

	std::ofstream saveFile("level.txt");

	GameObject::SaveObjects(saveFile, gameObjects);

	saveFile.close();

	// free up the game objects
	for (GameObject* objectPtr : gameObjects)
	{
		delete objectPtr;
	}
	gameObjects.clear();

	std::ifstream loadFile("level.txt");

	gameObjects = GameObject::LoadObjects(loadFile);

	// find the player
	for (GameObject* objectPtr : gameObjects)
	{
		playerPtr = dynamic_cast<Player*>(objectPtr);

		if (playerPtr)
			break;
	}

	loadFile.close();
}

void GameManager::EndPlay()
{

}

void GameManager::Update(double deltaTime)
{

}

void GameManager::Render(Gdiplus::Graphics& canvas, const CRect& clientRect)
{
	////////////////////////////////////////////////////////////////////////////////
	// Begin example code

	// Save the current transformation of the scene
	Gdiplus::Matrix transform;
	canvas.GetTransform(&transform);
	
	// Offset by the negative of the player direction
	canvas.TranslateTransform(-(Gdiplus::REAL)playerPtr->location.X, -(Gdiplus::REAL)playerPtr->location.Y);
	
	int numRows = clientRect.Height() / CellSize;
	int numCols = clientRect.Width() / CellSize;

	// draw horizontal lines
	for (int row = 0; row < numRows; ++row)
	{
		Vector2i start = Vector2i(0, row * CellSize);
		Vector2i end = Vector2i(clientRect.Width(), row * CellSize);
		GameFrameworkInstance.DrawLine(canvas,
			start,
			end,
			Gdiplus::Color::HotPink);
	}

	// draw vertical lines
	for (int col = 0; col < numCols; ++col)
	{
		Vector2i start = Vector2i(col * CellSize, 0);
		Vector2i end = Vector2i(col * CellSize, clientRect.Height());
		GameFrameworkInstance.DrawLine(canvas,
			start,
			end,
			Gdiplus::Color::DeepPink);
	}

	// Draw all of the objects
	for (GameObject* objectPtr : gameObjects)
	{
		objectPtr->Render(canvas);
	}

	// Render method demonstration (You can remove all of this code)
	GameFrameworkInstance.DrawLine(canvas, Vector2i(200, 200), Vector2i(400, 200), Gdiplus::Color::White);

	GameFrameworkInstance.DrawRectangle(canvas, AABBi(Vector2i(10, 110), Vector2i(100, 200)), false, Gdiplus::Color::White);
	GameFrameworkInstance.DrawRectangle(canvas, AABBi(Vector2i(200, 110), Vector2i(300, 200)), true, Gdiplus::Color::White);

	//// restore the transform
	//canvas.SetTransform(&transform);

	GameFrameworkInstance.DrawCircle(canvas, Vector2i(200, 200), 50, false, Gdiplus::Color::White);
	GameFrameworkInstance.DrawCircle(canvas, Vector2i(400, 200), 50, true, Gdiplus::Color::White);

	GameFrameworkInstance.DrawText(canvas, Vector2i(10, 300), 12, "Arial", "Hello World!", Gdiplus::Color::White);

	// Load the image file Untitled.png from the Images folder. Give it the unique name of Image1
	ImageWrapper* image1 = GameFrameworkInstance.GetLoadedImage(Image1);
	GameFrameworkInstance.DrawImage(canvas, Vector2i(400, 400), image1);

	// Restore the transformation of the scene
	canvas.SetTransform(&transform);

	// End example code
	////////////////////////////////////////////////////////////////////////////////
}

void GameManager::SetPlayerInput(const Vector2i& newInput)
{
	playerInput = newInput;

	// move the player
	playerPtr->location += playerInput;
}

void GameManager::OnMouseClick(const Vector2i & location)
{
	// need to get our actual location as we can move off of the screen
	Vector2i actualLocation = location + playerPtr->location;

	GameObject* toDelete = nullptr;

	// Convert the pixel coordinates to the grid cell coordinates
	int gridX = (actualLocation.X - (actualLocation.X % CellSize)) / CellSize;
	int gridY = (actualLocation.Y - (actualLocation.Y % CellSize)) / CellSize;

	// generate a bounding box for the grid cell
	Vector2i boxMin = Vector2i(gridX * CellSize, gridY * CellSize);
	Vector2i boxMax = boxMin + Vector2i(CellSize, CellSize);
	AABBi gridBounds = AABBi(boxMin, boxMax);

	for (GameObject* objectPtr : gameObjects)
	{
		GameObject& objectRef = *objectPtr;

		AABBi bounds(objectRef.location - Vector2i(10, 10),
			objectRef.location + Vector2i(10, 10));

		// clicked on this game object?
		if (bounds.Contains(actualLocation))
		{
			toDelete = objectPtr;
		}
	}

	if (toDelete)
	{
		gameObjects.erase(std::find(gameObjects.begin(), gameObjects.end(), toDelete));
		delete toDelete;
	}
	else
	{
		// instantiate a new Saving where we clicked
		Saving* newObject = new Saving(gridBounds.Centre());
		gameObjects.push_back(newObject);
	}
}
