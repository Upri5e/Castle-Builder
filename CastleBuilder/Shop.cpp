#include "Shop.h"
#include "pugi/pugixml.hpp"
#include <filesystem>
#include <set>

TransformComponent buttonPos;

using namespace std;
namespace fs = std::filesystem;

Shop::Shop(int x, int y)
{
	transform = addComponent<TransformComponent>(x, y);

	//Create the shop button
	button = new Button(transform.x(), transform.y(), "img/shop.png");
	button->SetName("Shop Button");
	Game::manager.AddEntity(button);

	//Load Shop.xml
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/shop.xml");

	if (!result)
	{
		std::cout << "ERROR: " << result.description() << std::endl;
		return;
	}
	pugi::xml_node root = doc.child("root");

	//Filter shop categories and items from shop.xml
	for (auto node : root.children())
	{
		Category tempCat;
		tempCat.name = node.name();
		for (auto item : node.children())
		{
			ShopItem shopItem;
			shopItem.name = item.name();
			shopItem.category = node.name();
			shopItem.cost = item.attribute("cost").as_int();
			shopItem.levelCap = item.attribute("levelCap").as_int();
			shopItem.value = item.attribute("value").as_int();
			shopItem.url = "img/" + tempCat.name + "/" + item.attribute("url").as_string();
			shopItem.id = item.attribute("uid").as_int();
			tempCat.itemsInShop.push_back(shopItem);
		}
		categoriesInShop.push_back(tempCat);

	}
}

Shop::~Shop()
{
}

void Shop::Update()
{
	Entity::Update();
}

