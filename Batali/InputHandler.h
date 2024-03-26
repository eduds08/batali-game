#pragma once

#include "RunCommand.h"
#include "JumpCommand.h"
#include "Attack1Command.h"
#include "Attack2Command.h"
#include "RollCommand.h"
#include "UltimateCommand.h"

#include <SFML/Graphics.hpp>

class InputHandler
{
public:
	InputHandler() {}

	~InputHandler()
	{
		delete m_runRightCommand;
		m_runRightCommand = nullptr;

		delete m_runLeftCommand;
		m_runLeftCommand = nullptr;

		delete m_jumpCommand;
		m_jumpCommand = nullptr;

		delete m_attack1Command;
		m_attack1Command = nullptr;

		delete m_attack2Command;
		m_attack2Command = nullptr;

		delete m_rollCommand;
		m_rollCommand = nullptr;

		delete m_ultimateCommand;
		m_ultimateCommand = nullptr;
	}

	void handleInput(Character& character);

	void bindRunRightCommand(sf::Keyboard::Scancode button)
	{
		m_runRightCommand = new RunCommand{};
		m_runRightCommand->button = button;
	}

	void bindRunLeftCommand(sf::Keyboard::Scancode button)
	{
		m_runLeftCommand = new RunCommand{};
		m_runLeftCommand->button = button;
	}

	void bindJumpCommand(sf::Keyboard::Scancode button) 
	{
		m_jumpCommand = new JumpCommand{};
		m_jumpCommand->button = button; 
	}

	void bindAttack1Command(sf::Keyboard::Scancode button)
	{
		m_attack1Command = new Attack1Command{};
		m_attack1Command->button = button;
	}

	void bindAttack2Command(sf::Keyboard::Scancode button)
	{
		m_attack2Command = new Attack2Command{};
		m_attack2Command->button = button;
	}

	void bindRollCommand(sf::Keyboard::Scancode button)
	{
		m_rollCommand = new RollCommand{};
		m_rollCommand->button = button;
	}

	void bindUltimateCommand(sf::Keyboard::Scancode button)
	{
		m_ultimateCommand = new UltimateCommand{};
		m_ultimateCommand->button = button;
	}

private:
	Command* m_runRightCommand{};
	Command* m_runLeftCommand{};
	Command* m_jumpCommand{};
	Command* m_attack1Command{};
	Command* m_attack2Command{};
	Command* m_rollCommand{};
	Command* m_ultimateCommand{};
};
