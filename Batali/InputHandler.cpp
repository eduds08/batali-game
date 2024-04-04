#include "InputHandler.h"

#include <iostream>

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
	m_bindCommands.clear();
}

std::shared_ptr<ICommand> InputHandler::handleInput()
{
	for (const auto& bindCommand : m_bindCommands)
	{
		if (sf::Keyboard::isKeyPressed(bindCommand.first))
		{
			return bindCommand.second;
		}
	}

	return nullptr;
}
