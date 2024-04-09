#pragma once
#include "ECS/Components.h"
#include "SDL.h"
#include "Button.h"

class Buildings : public Entity
{
public:
	Buildings(int uid, int cost, int value, int levelCap, const char* texture, const char* name, const char* categoryName, int x, int y);
	~Buildings();

	void Update() override;

	Button* button;
	const char* Name;

	int GetUID();
	const char* Texture;
	TransformComponent transform;

private:
	int Uid;
	int Cost;
	int Value;
	const char* CategoryName;
	int LevelCap;
};
