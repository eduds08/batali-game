#include "ProjectileRenderComponent.h"

#include "GameObject.h"

void ProjectileRenderComponent::render(GameObject& gameObject, sf::RenderWindow& window)
{
	window.draw(gameObject.getShape());
	window.draw(gameObject.getSprite());
}
