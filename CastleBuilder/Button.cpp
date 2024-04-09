#include "Button.h"
#include "Input.h"

Button::Button(int x, int y, const char* path, void (*Callback)())
{
	transform = addComponent<TransformComponent>(x, y);
	spriteComponent = addComponent<SpriteComponent>(path);
	callback = Callback;
	texturePath = path;
}

Button::~Button()
{
}

void Button::Update() 
{
	Entity::Update();
	shapeRect = { transform.x(), transform.y(), 100, 100 };

	int mouseX, mouseY;
	//Check if mouse pointer is over the button
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Point point = { mouseX, mouseY };
	if(SDL_PointInRect(&point, &shapeRect))
	{
		if (Input::GetInstance()->GetMouseButtonDown(LEFT) && isReleased) //Button Clicked
		{
			isReleased = false;
			if(callback)
				callback();
			if (OnButtonClicked)
				OnButtonClicked(this);
		}
		else
		{
			isReleased = true;
		}
	}
}