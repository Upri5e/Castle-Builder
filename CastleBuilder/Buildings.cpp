#include "Buildings.h"
#include "TextureManager.h"
#include "GUI/Widget.h"

Buildings::Buildings(int uid, int cost, int value, int levelCap, const char* texture, const char* name, const char* categoryName, int x, int y)
{
	Uid = uid;
	Cost = cost;
	Value = value;
	CategoryName = categoryName;
	Name = name;
	LevelCap = levelCap; 
	transform = addComponent<TransformComponent>(x, y);
	Texture = texture;
	
	//Create building button
	button = new Button(transform.x(), transform.y(), texture);
	button->SetName(Name);
	button->parent = this;
	Game::manager.AddEntity(button);

	//View Delete prompt when building is clicked
	button->OnButtonClicked = [](Button* button) { Widget::BuildingDeletePrompt(button); };
}

Buildings::~Buildings()
{
}
void Buildings::Update()
{
	Entity::Update();
}
int Buildings::GetUID() {
	return Uid;
}
