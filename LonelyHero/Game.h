#pragma once

#include <SFML/Graphics.hpp>
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

	bool isColliding(const Ground& ground);

private:
	sf::RenderWindow m_window{ sf::VideoMode(600, 600), "Lonely Hero" };
	
	sf::Clock clock{};
	sf::Event m_event{};

	float m_deltaTime{};

	Player m_player{ 120, 80, 10, 0.1f };
};
