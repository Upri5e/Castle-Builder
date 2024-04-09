#pragma once
#include "Button.h"

struct ShopItem
{
	int id;
	std::string name;
	std::string url;
	int cost;
	int value;
	int levelCap;
	std::string category;
};
struct Category
{
	std::string name;
	std::vector<ShopItem> itemsInShop;
};
class Shop : public Entity
{
public:
	Shop(int x, int y);
	~Shop();

	TransformComponent transform;

	void Update() override;

	Button* button;

	bool isOpen = false;

	std::vector<Category> categoriesInShop;
private:
};

