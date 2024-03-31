#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>

#include "ICommand.h"

class InputHandler
{
public:
	InputHandler();
	virtual ~InputHandler();

	ICommand* handleInput();

	std::unordered_map<sf::Keyboard::Scancode, ICommand*> m_bindCommands{};
};
