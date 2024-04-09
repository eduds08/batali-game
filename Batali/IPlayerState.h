#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class Player;

class IPlayerState
{
public:
	virtual ~IPlayerState() = default;

	virtual std::unique_ptr<IPlayerState> handleCondition(Player& player, const std::string& condition) = 0;

	virtual std::unique_ptr<IPlayerState> handleInput(Player& player, sf::Keyboard::Scancode input) = 0;
	virtual void update(Player& player) = 0;

	virtual void enter(Player& player) = 0;
};
