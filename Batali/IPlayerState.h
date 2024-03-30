#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class Player;

class IPlayerState
{
public:
	virtual ~IPlayerState() = default;

	virtual IPlayerState* handleInput(Player& player, sf::Keyboard::Scancode input, bool release = false) = 0;
	virtual void update(Player& player) = 0;

	virtual void enter(Player& player) = 0;
};
