#include "Map.h"
#include "TextureManager.h"
#include "pugi/pugixml.hpp"
#include "Buildings.h"
#include "GUI/Widget.h"

int defaultMap[10][10] = { //Default map in case map wasnt loaded
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,0,0,0,0,0,0,-1,-1},
		{-1,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,-1},
		{-1,-1,0,0,0,0,0,0,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
}; 
pugi::xml_document doc;

Map::Map(Shop* mshop, const char* path)
{
	shop = mshop; //Ref to shop so we can know what bldngs the IDs represent
	transform = addComponent<TransformComponent>();

	bgTexture = TextureManager::LoadTexture(path);//Should have added a spritecomponent with w and h variables to fit screen

	mapXGrids = 10;
	mapYGrids = 10;
}

Map::~Map()
{
}

void Map::LoadMap(const char* path, int positionX, int positionY, int w, int h)
{
	pugi::xml_parse_result result = doc.load_file(path);

	if (!result)
	{
		//If xml doesnt load, create it with default map then load map afterwards
		SaveMapXml(path, defaultMap);
		LoadMap(path, positionX, positionY, w, h);
		return;
	}
	pugi::xml_node root = doc.child("root");
	//Set play area based on map size
	Game::SetPlayArea(root.attribute("width").as_int(), root.attribute("height").as_int());

	//Set values to center the playarea
	int playAreaHalfWidth = w / 2;
	int playAreaHalfHeight = h / 2;
	int screenCenterX = positionX / 2;
	int screenCenterY = positionY / 2;

	gridWidth = Game::playAreaWidth / mapXGrids;
	gridHeight = Game::playAreaHeight / mapYGrids;

	transform.SetPosition(screenCenterX - playAreaHalfWidth, screenCenterY - playAreaHalfHeight);
	//applying rect values to use on map draw
	mapRect.x = transform.x();
	mapRect.y = transform.y();

	mapRect.w = Game::playAreaWidth = w;
	mapRect.h = Game::playAreaHeight = h;
	//Get map tile values from xml
	for (auto& node : root.children())
	{
		int x = node.attribute("x").as_int();
		int y = node.attribute("y").as_int();
		int value = node.attribute("value").as_int();
		map[x][y] = value;
	}

	drawRect.w = gridWidth;
	drawRect.h = gridHeight;
	std::vector<ShopItem> allItems;

	//Load all available items from shop into an array
	for (int i = 0; i < shop->categoriesInShop.size(); i++)
	{
		allItems.insert(allItems.end(), shop->categoriesInShop[i].itemsInShop.begin(), shop->categoriesInShop[i].itemsInShop.end());
	}
	for (int row = 0; row < mapXGrids; row++)
	{
		for (int column = 0; column < mapYGrids; column++)
		{
			//Set bldng position based on map tile
			drawRect.y = transform.y() + column * gridHeight;
			drawRect.x = transform.x() + row * gridWidth;

			int buldID = map[row][column];
			if (buldID > 0)
			{
				//Draw Items based on ID 
				for (ShopItem item : allItems)
				{
					if (item.id == buldID)
					{
						Buildings* building = new Buildings(1, item.cost, item.value, item.levelCap, item.url.c_str(), item.name.c_str(), item.category.c_str(), drawRect.x, drawRect.y);
						building->SetName(item.name.c_str());
						Game::manager.AddEntity(building);
						if (onBuildingAdded)
							onBuildingAdded(building);

						std::cout << building->GetName() << std::endl;
					}
				}

			}
		}
	}
}
void Map::SaveMapXml(const char* path, int arr[10][10])
{
	//Create an xml with the default map values
	pugi::xml_node rootNode = doc.append_child("root");
	rootNode.append_attribute("width") = "800";
	rootNode.append_attribute("height") = "640";
	for (int row = 0; row < mapXGrids; row++)
	{
		for (int column = 0; column < mapYGrids; column++)
		{
			const char* name = "coordinate";
			pugi::xml_node node = rootNode.append_child(name);
			node.append_attribute("x") = row;
			node.append_attribute("y") = column;
			std::string str = std::to_string(arr[row][column]);
			const char* value = str.c_str();
			node.append_attribute("value") = value;
		}
	}
	doc.save_file(path);
}

//Redundant, could use the managers draw function to draw the map with the sprite component instead
void Map::DrawMap()
{
	//Draw background Image
	TextureManager::Draw(bgTexture, mapRect);
}
int Map::GetHeight()
{
	return mapYGrids * gridHeight;
}
int Map::GetWidth()
{
	return mapXGrids * gridWidth;
}

