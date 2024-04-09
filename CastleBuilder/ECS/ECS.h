#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentTypeID = std::size_t;

inline ComponentTypeID getComponentTypeID()
{
	static ComponentTypeID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentTypeID getComponentTypeID() noexcept //No exceptions
{
	static ComponentTypeID typeID = getComponentTypeID(); //Should be const
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	Component() {}
	virtual ~Component() {}
};

class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

	const char* name = "Entity";
public:

	Entity() {}
	virtual ~Entity() {}

	virtual void Update()
	{
		for (auto& c : components) c->Update();
	}
	void Draw() 
	{
		for (auto& c : components) c->Draw();
	}
	bool isActive() const { return active; }
	void Destroy() { active = false; }

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs> //Template with undefined number of arguements
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...)); //Create new component of type T on the heap and forward all args
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c }; //Convert component to upointer to store
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template <typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
	void SetName(const char* fname) {
		name = fname;
	}
	const char* GetName() {
		return name;
	}
};

class ECS_Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void Update()
	{
		for (auto& e : entities) e->Update();
	}

	void Draw()
	{
		for (auto& e : entities) e->Draw();
	}

	void Refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	void AddEntity(Entity* entity)
	{
		std::unique_ptr<Entity> uPtr{ entity };
		entities.emplace_back(std::move(uPtr));
	}
};