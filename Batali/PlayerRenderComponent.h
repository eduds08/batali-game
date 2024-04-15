#pragma once

#include "IRenderComponent.h"
#include <SFML/Graphics.hpp>

#include "Player.h"

class PlayerRenderComponent : public IRenderComponent
{
public:
	PlayerRenderComponent() = default;
	virtual ~PlayerRenderComponent() = default;

	virtual void render(GameObject& gameObject, sf::RenderWindow& window);
};
