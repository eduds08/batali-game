#pragma once

#include "Player.h"
#include "Enemy.h"
#include "HealthBarUI.h"
#include "Ground.h"
#include <fstream>
#include <vector>
#include <thread>
#include <string>

using namespace constants;

class MenuContext
{
public:
	MenuContext(sf::RenderWindow& window);
	virtual ~MenuContext() = default;

	virtual void update() = 0;
	virtual void render() = 0;

	const std::string& getCurrentState() { return m_currentState; }

protected:
	sf::RenderWindow& m_window;

	std::string m_currentState{};

	sf::Font m_font{};

	sf::View m_view{};
};
