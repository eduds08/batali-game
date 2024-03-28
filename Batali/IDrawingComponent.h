#pragma once

#include <SFML/Graphics.hpp>

class Player;

class IDrawingComponent
{
public:
	virtual ~IDrawingComponent() = default;

	virtual void render(Player& player, sf::RenderWindow& window) = 0;
};
