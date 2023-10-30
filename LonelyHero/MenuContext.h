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
	MenuContext(sf::RenderWindow& window, float& deltaTime);
	virtual ~MenuContext() = default;

	virtual void update() = 0;
	virtual void render() = 0;

	const std::string& getCurrentState() { return m_currentState; }

protected:
	sf::RenderWindow& m_window;
	float& m_deltaTime;

	std::string m_currentState{};

	sf::Font m_font{};

	sf::View m_view{};
};

