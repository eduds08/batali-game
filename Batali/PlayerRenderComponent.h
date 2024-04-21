#pragma once

#include "IRenderComponent.h"

class PlayerRenderComponent : public IRenderComponent
{
public:
	PlayerRenderComponent() = default;
	virtual ~PlayerRenderComponent() = default;

	virtual void render(GameObject& gameObject, sf::RenderWindow& window);
};
