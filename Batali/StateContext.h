#pragma once

#include "SFML/Graphics.hpp"
#include "Constants.h"
#include <string>
#include <vector>

using namespace constants;

class StateContext
{
public:
	StateContext(sf::RenderWindow& window);
	virtual ~StateContext() = default;

	virtual void update() = 0;
	virtual void render() = 0;

	const std::string& getCurrentState() { return m_currentState; }
	void setCurrentState(const std::string& stateName) { m_currentState = stateName; }

	void setPressedKey(sf::Keyboard::Scancode pressedKey) { m_pressedKey = pressedKey; }

protected:
	sf::RenderWindow& m_window;
	sf::Event m_event{};

	std::string m_currentState{};

	sf::Font m_font{};

	sf::View m_view{};

	sf::Keyboard::Scancode m_pressedKey{};
};
