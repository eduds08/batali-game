#pragma once

class Character;
#include <SFML/Graphics.hpp>

class Command
{
public:
	virtual ~Command() = default;
	virtual void execute(Character& character) = 0;

	sf::Keyboard::Scancode button;
};
