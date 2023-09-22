#pragma once

#include <vector>
#include "Player.h"
#include "Ground.h"

class Game
{
public:
	Game();
	~Game();

	void init();
	void update();
	void render();
	void run();

	std::vector<Ground> grounds{};

private:
	sf::RenderWindow m_window{ sf::VideoMode(600, 600), "Lonely Hero" };
	
	sf::Clock clock{};
	sf::Event m_event{};
	float m_deltaTime{};

	Player m_player{ 120, 80, 30.f, 80.f, 10, 0.1f };
};
