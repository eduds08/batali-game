#pragma once

#include "IDrawingComponent.h"
#include <SFML/Graphics.hpp>

#include "Player.h"

class PlayerDrawingComponent : public IDrawingComponent
{
public:
	PlayerDrawingComponent();
	virtual ~PlayerDrawingComponent();

	virtual void render(Player& player, sf::RenderWindow& window);
private:
	sf::Sprite m_sprite{};


};
