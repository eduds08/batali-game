#include "HoodieState.h"

#include "Player.h"

HoodieState::HoodieState()
{
}

HoodieState::~HoodieState()
{
}

void HoodieState::enter(Player& player)
{
	/*player.setSpriteSize(sf::Vector2i{ BOXER_SPRITE_WIDTH, BOXER_SPRITE_HEIGHT });
	player.getShape().setSize(sf::Vector2f{ BOXER_SHAPE_WIDTH, BOXER_SHAPE_HEIGHT });

	player.getSprite().setOrigin(player.getSpriteSize().x / 2.f, player.getSpriteSize().y / 2.f);

	player.getShape().setOrigin(player.getShape().getSize() / 2.f);*/
}

void HoodieState::updateAttackHitbox(Player& player, AttackHitbox& attackHitbox)
{
}

void HoodieState::checkIfIsAttacking(Player& player, Player& enemy, AttackHitbox& attackHitbox)
{
}
