#include "InputHandler.h"

#include <iostream>

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
	std::unordered_map<sf::Keyboard::Scancode, ICommand*>::iterator itr = m_bindCommands.begin();

	for (std::unordered_map<sf::Keyboard::Scancode, ICommand*>::iterator itr = m_bindCommands.begin(); itr != m_bindCommands.end(); ++itr)
	{
		delete itr->second;
		itr->second = nullptr;
	}

	m_bindCommands.clear();

	delete testeLeft;
	delete testeRight;
}

ICommand* InputHandler::handleInput()
{
	for (const auto& bindCommand : m_bindCommands)
	{
		if (sf::Keyboard::isKeyPressed(bindCommand.first))
		{
			return bindCommand.second;
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
	{
		return testeLeft;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
	{
		return testeRight;
	}

	return nullptr;
}
