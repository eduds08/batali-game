#include "PlayerDrawingComponent.h"

PlayerDrawingComponent::PlayerDrawingComponent()
{

}

PlayerDrawingComponent::~PlayerDrawingComponent()
{

}

void PlayerDrawingComponent::render(Player& player, sf::RenderWindow& window)
{
	window.draw(player.getSprite());
}
