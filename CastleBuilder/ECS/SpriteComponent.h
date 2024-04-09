#pragma once

#include "Components.h"
#include "../TextureManager.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		SetTexture(path);
	}
	
	void SetTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void Init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		destRect.w = destRect.h = 100; //Should have changed this to a variable
	}

	void Update() override
	{
		destRect.x = transform->x();
		destRect.y = transform->y();
	}

	void Draw() override
	{
		TextureManager::Draw(texture, destRect);
	}
};