#pragma once

#include "Game.h"
#include "ECS/Components.h"
#include "Shop.h"
#include "Buildings.h"

class Map : public Entity
{
public:
	Map(Shop* mshop,const char* path);
	~Map();

	void LoadMap(const char* path, int positionX, int positionY, int w, int h);
	void DrawMap();
	int GetHeight();
	int GetWidth();
	void (*onBuildingAdded) (Buildings* building);

private:
	TransformComponent transform;

	SDL_Rect drawRect, mapRect;

	//TODO: Move to a seperate file that reads xml items and creates texture for each
	SDL_Texture* drugStore;
	SDL_Texture* bgTexture;
	int map[10][10];
	int gridWidth, gridHeight;
	int mapXGrids, mapYGrids;
	int playAreaWidth, playAreaHeight;

	Shop* shop;
	void SaveMapXml(const char* path, int arr[10][10]);
};