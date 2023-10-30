#pragma once

#include "PlayingState.h"
#include "MainMenuState.h"

class Game
{
public:
	Game();
	~Game();

	void run();
	void update();
	void render();

private:
	sf::RenderWindow m_window{ sf::VideoMode(screenWidth, screenHeight), "Lonely Hero" };

	sf::Event m_event{};

	sf::Clock m_deltaTimeClock{};
	float m_deltaTime{};

	MenuContext* m_menuContext;
};
