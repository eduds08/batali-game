#include "InputHandler.h"

#include <iostream>

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
	/*std::unordered_map<sf::Keyboard::Scancode, std::shared_ptr<ICommand>>::iterator itr = m_bindCommands.begin();

	for (std::unordered_map<sf::Keyboard::Scancode, std::shared_ptr<ICommand>>::iterator itr = m_bindCommands.begin(); itr != m_bindCommands.end(); ++itr)
	{
		delete itr->second;
		itr->second = nullptr;
	}*/

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
