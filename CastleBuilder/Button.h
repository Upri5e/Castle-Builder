#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "SDL_mouse.h"
#include "ECS/Components.h"

enum ButtonState {NORMAL=0, HOVER=1, SELECTED=2};
class Button : public Entity
{
public:
	SDL_Texture* texture;
	SDL_Rect desRect;
	const char* texturePath;
	Button(int x, int y, const char* path, void (*Callback)() = NULL);
	virtual ~Button();

	void Update() override;

	void (*OnButtonClicked) (Button* button);

	Entity* parent;
private:
	void (*callback)();
	SDL_Rect shapeRect;
	bool isReleased = true;
	SpriteComponent spriteComponent;
	TransformComponent transform;
};

