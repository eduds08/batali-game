#pragma once

#include "IRenderComponent.h"

class ProjectileRenderComponent : public IRenderComponent
{
public:
	ProjectileRenderComponent() = default;
	virtual ~ProjectileRenderComponent() = default;


	virtual void render(GameObject& gameObject, sf::RenderWindow& window);
};
