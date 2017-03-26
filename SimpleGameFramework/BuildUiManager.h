#pragma once
class BuildUiManager
{
public:
	BuildUiManager();
	~BuildUiManager();
protected:
	virtual void RenderInternal(Gdiplus::Graphics& canvas);
};