#pragma once

#include "IPlayerState.h"

class PlayerHittedState : public IPlayerState
{
public:
	PlayerHittedState(Player& player, int enemyDamage, bool fastHit = false, bool frozen = false);
	virtual ~PlayerHittedState() = default;

	virtual std::unique_ptr<IPlayerState> handleHitted(Player& player, int enemyDamage, bool fastHit = false, bool frozen = false);

	virtual std::unique_ptr<IPlayerState> handleInput(Player& player, sf::Keyboard::Scancode input);
	virtual void update(Player& player);

	virtual void enter(Player& player);

private:
	bool m_fastHit{ false };
	bool m_frozen{ false };
};
