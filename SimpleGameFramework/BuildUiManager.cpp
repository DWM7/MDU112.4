#include "stdafx.h"
#include "BuildUiManager.h"
#include "GameManager.h"


BuildUiManager::BuildUiManager()
{
}


BuildUiManager::~BuildUiManager()
{
}

void BuildUiManager::RenderInternal(Gdiplus::Graphics & canvas)
{
	Vector2i dimensions = GameManagerInstance.GetScreenDimensions();
	Vector2i centrePoint = dimensions * 0.5f;
	// centre the UI in the view
	GameFrameworkInstance.DrawRectangle(canvas,
		AABBi(Vector2i(-10, -10) + centrePoint-10,
			Vector2i(10, 10) + centrePoint+10),
		true, Gdiplus::Color::Yellow);
}