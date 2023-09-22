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
private:
	sf::RenderWindow m_window{ sf::VideoMode(600, 600), "Lonely Hero" };
	
	sf::Clock m_clock{};
	sf::Event m_event{};
	float m_deltaTime{};

	Player m_player{ 120, 80, 30.f, 80.f, 10, 0.1f };
	std::vector<Ground> grounds{};
};
