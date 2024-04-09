#pragma once
#include "Components.h"

class TransformComponent : public Component
{
private:
	int xPos;
	int yPos;

public:
	int x() { return xPos; }
	int y() { return yPos; }

	TransformComponent()
	{
		xPos = 0;
		yPos = 0;
	}

	TransformComponent(int x, int y)
	{
		xPos = x;
		yPos = y;
	}

	void Update() override
	{
	}

	void SetPosition(int x, int y)
	{
		xPos = x;
		yPos = y;
	}
};