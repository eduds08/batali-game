#pragma once

#include "PlayingState.h"
#include "MainMenuState.h"
#include <windows.h>

class Game
{
public:
	Game();
	~Game();

	void run();
	void update();
	void render();

private:
	sf::RenderWindow m_window{ sf::VideoMode().getDesktopMode(), "Lonely Hero" };

	sf::Event m_event{};

	sf::Clock m_deltaTimeClock{};
	float m_deltaTime{};

	StateContext* m_stateContext;
};
