#include "InputHandler.h"

#include <iostream>

#include "Player.h"

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
	m_bindCommands.clear();
}

void InputHandler::handleInput(Player& player)
{
	for (const auto& bindCommand : m_bindCommands)
	{
		if (sf::Keyboard::isKeyPressed(bindCommand.first))
		{
			bindCommand.second->execute(player);
		}
	}
}
