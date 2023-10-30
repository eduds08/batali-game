#pragma once

#include "SFML/Graphics.hpp"
#include "Game.h"
#include "MainMenu.h"

class PrincipalTemporario
{
public:
	PrincipalTemporario();
	~PrincipalTemporario();

	void init();
	void run();
	void update();
	void render();

protected:
	Game* playingState;
	MainMenu* menuState;

	sf::RenderWindow m_window{ sf::VideoMode(screenWidth, screenHeight), "Lonely Hero" };

	sf::Event m_event{};

	sf::Clock m_deltaTimeClock{};
	float m_deltaTime{};
};

