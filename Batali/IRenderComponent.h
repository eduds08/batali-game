#pragma once

#include <SFML/Graphics.hpp>

class GameObject;

class IRenderComponent
{
public:
	virtual ~IRenderComponent() = default;

	virtual void render(GameObject& gameObject, sf::RenderWindow& window) = 0;
};
