#include "PlayerRenderComponent.h"

#include "IAttackComponent.h"

#include "AttackHitbox.h"

#include "Player.h"

void PlayerRenderComponent::render(GameObject& gameObject, sf::RenderWindow& window)
{
	window.draw(gameObject.getShape());
	window.draw(gameObject.getSprite());

	Player* player = dynamic_cast<Player*>(&gameObject);

	window.draw(player->getChosenCharacter()->getAttackHitbox().getShape());
}
