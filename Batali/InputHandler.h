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

	//ICommand* handleInput();
	void handleInput(Player& player);

	std::unordered_map<sf::Keyboard::Scancode, std::shared_ptr<ICommand>> m_bindCommands{};
};
