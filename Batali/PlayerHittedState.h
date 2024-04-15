#pragma once

#include "IPlayerState.h"

class PlayerHittedState : public IPlayerState
{
public:
	PlayerHittedState(Player& player, int enemyDamage, float knockbackVelocity);
	virtual ~PlayerHittedState() = default;

	virtual std::unique_ptr<IPlayerState> handleHitted(Player& player, int enemyDamage, float knockbackVelocity);

	virtual std::unique_ptr<IPlayerState> handleInput(Player& player, sf::Keyboard::Scancode input);
	virtual void update(Player& player);

	virtual void enter(Player& player);

private:
	float m_knockbackVelocity{};
};
