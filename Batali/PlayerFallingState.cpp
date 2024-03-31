#include "PlayerFallingState.h"

#include "Player.h"

PlayerFallingState::PlayerFallingState()
{
}

PlayerFallingState::~PlayerFallingState()
{
}

IPlayerState* PlayerFallingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerFallingState::update(Player& player)
{
	if (sf::Keyboard::isKeyPressed(player.RUN_RIGHT_BUTTON))
	{
		player.m_facingRight = 1;
		player.getVelocity().x = 200.f * player.m_facingRight;
	}
	else if (sf::Keyboard::isKeyPressed(player.RUN_LEFT_BUTTON))
	{
		player.m_facingRight = -1;
		player.getVelocity().x = 200.f * player.m_facingRight;
	}

	if (player.getVelocity().y == 0.f)
	{
		player.setPlayerState(new PlayerIdleState());
	}
}

void PlayerFallingState::enter(Player& player)
{
	player.getAnimatingComponent()->setNewAnimation(player, FALLING_ANIMATION, true);
}
