#pragma once

#include "GameFramework.h"
#include "Player.h"
#include "GameInput.h"

#include <list>

const int CellSize = 20;

class GameManager
{
public:
	bool object_choice = true;
	bool floor_choice = false;
	bool build_mode = true;
	static GameManager& Instance();

	/** BeginPlay is called when the game first launches. It is only called once per launch. */
	void BeginPlay();

	/** EndPlay is called when the game is closing down. It is only called once and only on exit. */
	void EndPlay();

	/**
	 * Update is called every frame. Update is always called before render
	 *
	 * @param deltaTime The time in seconds since Update was last called.
	 */
	void Update(double deltaTime);

	/**
	 * Render is called every frame after Update is called. All drawing must happen in render.
	 *
	 * @param [in,out] canvas The canvas.
	 * @param clientRect	  The rectangle representing the drawable area.
	 */
	void Render(Gdiplus::Graphics& canvas, const CRect& clientRect);

	void SetPlayerInput(const Vector2i& newInput);
	void OnMouseClick(const Vector2i& location);

	const Vector2i& GetScreenDimensions() const
	{
		return screenDimensions;
	}

private:
	GameManager();
	~GameManager();

	Vector2i playerInput;

	std::list<GameObject*> gameObjects;
	Player* playerPtr;

	Vector2i screenDimensions;
};

/**
 * Retrieves the GameManagerInstance for the game.
 *
 * @return The game manager instance
 */
#define GameManagerInstance (GameManager::Instance())
