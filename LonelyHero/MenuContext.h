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

	virtual void init() = 0;
	//void run();
	virtual void update() = 0;
	virtual void render() = 0;

protected:
	sf::RenderWindow& m_window;

	float& m_deltaTime;
};

