#pragma once

#include "IRenderComponent.h"
#include <SFML/Graphics.hpp>

#include "Player.h"

class PlayerRenderComponent : public IRenderComponent
{
public:
	PlayerRenderComponent();
	virtual ~PlayerRenderComponent();

	virtual void render(GameObject& gameObject, sf::RenderWindow& window);
};
