#include "Widget.h"
#include "sdlui.h"
#include "../Shop.h"
#include "../Map.h"

Widget* Widget::instance = nullptr;

SDLUI_Control_Window* shopWindow;
SDLUI_Control_TabContainer* shopTabContainer;
Shop* shop;

std::vector<SDLUI_Control_Button*> buttonsRender;
SDLUI_Control_Window* deletePrompt;
SDLUI_Control_Button* deleteBtn;

Map* map;
Entity* selectedEntity;


void ToggleWindow(SDLUI_Control_Window* window)
{
	if (!window->visible)
	{
		window->visible = true;
	}
}

Widget::Widget()
{
}

void Widget::BuildingDeletePrompt(Button* button)
{
	//Modify the delete prompt position and values to selected building
	TransformComponent transform = button->getComponent<TransformComponent>();
	deletePrompt->x = transform.x() + 100;
	deletePrompt->y = transform.y();

	selectedEntity = button->parent;
	//Check SDLUI Text not showing
	std::string Name = button->GetName();
	std::string Title = "Delete" + Name + "?";
	deletePrompt->title.modify(Title.c_str());
	deleteBtn->text.modify(Title.c_str());
	deleteBtn->x = deletePrompt->x + (deletePrompt->w / 2) -(deleteBtn->w / 2);
	deleteBtn->y = deletePrompt->y + (deletePrompt->h / 2) - (deleteBtn->h / 2) + 10;
	if (!deletePrompt->visible)
		deletePrompt->visible = true;
}

void Widget::LoadShop()
{
	shop = new Shop(Game::playAreaWidth - 100, Game::playAreaHeight - 100);
	shop->SetName("Shop");
	Game::manager.AddEntity(shop);
	TransformComponent transform = shop->transform;


	shop->button->OnButtonClicked = [](Button* button) {ToggleWindow(shopWindow); };

	// Create shop window and tab container.
	shopWindow = SDLUI_CreateWindow(transform.x() - Game::playAreaWidth / 2, transform.y() - Game::playAreaHeight / 2, Game::playAreaWidth / 2, Game::playAreaHeight / 2, "Shop");
	shopWindow->can_be_resized = false;
	shopTabContainer = SDLUI_CreateTabContainer(shopWindow, 0, 25, shopWindow->w, shopWindow->h);

	//Create Tabs for shop categories
	for (int i = 0; i < shop->categoriesInShop.size(); i++) { //Loop through Categories
		shopTabContainer->add_tab(shop->categoriesInShop[i].name.c_str());
		//Grid the Tab
		for (int j = 0; j < shop->categoriesInShop[i].itemsInShop.size(); j++)
		{
			int column = j % 3;
			int row = j / 3;
			std::string path = shop->categoriesInShop[i].itemsInShop[j].url;
			SDLUI_Control_Button* item = SDLUI_CreateButton(shopWindow, 60, 30, &path[0]);
			
			//Set rect for buttons
			item->w = 100;
			item->h = 100;
			item->x = shopWindow->x + column * (item->w + 10) + 20;
			item->y = shopWindow->y + row * (item->h + 10) + 70;

			shopTabContainer->add_child(i, item);

			//TODO: Add items struct to vector as second param
			buttonsRender.insert(buttonsRender.begin(), item);
		}

	}
	
	shopTabContainer->set_active_tab(0);
	shopWindow->visible = false;
}

void Widget::Init(SDL_Renderer* renderer, SDL_Window* Window)
{
	//Initialize Shop and SDLUI
	SDLUI_Init(renderer, Window);
	LoadShop();

	//Create the map
	int windowWidth = 0; 
	int windowHeight = 0;
	SDL_GetWindowSize(Game::window, &windowWidth, &windowHeight);
	map = new Map(shop, "img/Map1.jpg");
	map->LoadMap("xml/map.xml", windowWidth, windowHeight, Game::playAreaWidth, Game::playAreaHeight);
	Game::manager.AddEntity(map);

	shop->transform.SetPosition(Game::playAreaWidth - 100, Game::playAreaHeight - 100);

	//Create the delete dialogue
	InitDeletePrompt();
}

void Widget::Update()
{
	// Manages SDLUI windows and their child controls
	SDLUI_WindowHandler();

	//Update shop window and Tabs Container
	SDLUI_Window(shopWindow);
	SDLUI_TabContainer(shopTabContainer);
	SDLUI_Window(deletePrompt);


	//Add Usage Functions
	if (SDLUI_Button(deleteBtn))
	{
		if (selectedEntity)
			std::cout << "Deleted " << selectedEntity->GetName() << std::endl;
	}

	for (SDLUI_Control_Button* button : buttonsRender)
		SDLUI_Button(button);

}

void Widget::Draw()
{
	//Not needed when Map entity is setup properly
	map->DrawMap();
	SDLUI_Render();
}

void Widget::EventHandle(SDL_Event event)
{
	//To Call event handler in Input.cpp
	SDLUI_EventHandler(event);
}

void Widget::InitDeletePrompt() {
	int promptHalfW = 250 / 2;
	int promptHalfH = 100 / 2;
	int playAreaCenterX = Game::playAreaWidth / 2;
	int playAreaCenterY = Game::playAreaHeight / 2;

	deletePrompt = SDLUI_CreateWindow(playAreaCenterX - promptHalfW, playAreaCenterY - promptHalfH, 250, 100, "Delete ?");
	deletePrompt->can_be_resized = false;
	deletePrompt->visible = false;

	deleteBtn = SDLUI_CreateButton(deletePrompt, 50, 20, "");//Text is not updating if I change it
}