#include "InputHandler.h"

void InputHandler::handleInput(Character& character)
{
	if (sf::Keyboard::isKeyPressed(m_runRightCommand->button))
	{
		m_runRightCommand->execute(character);
	}
	else if (sf::Keyboard::isKeyPressed(m_runLeftCommand->button))
	{
		m_runLeftCommand->execute(character);
	}
	if (sf::Keyboard::isKeyPressed(m_jumpCommand->button))
	{
		m_jumpCommand->execute(character);
	}
	if (sf::Keyboard::isKeyPressed(m_attack1Command->button))
	{
		m_attack1Command->execute(character);
	}
	if (sf::Keyboard::isKeyPressed(m_attack2Command->button))
	{
		m_attack2Command->execute(character);
	}
	if (sf::Keyboard::isKeyPressed(m_rollCommand->button))
	{
		m_rollCommand->execute(character);
	}
	if (sf::Keyboard::isKeyPressed(m_ultimateCommand->button))
	{
		m_ultimateCommand->execute(character);
	}
}
