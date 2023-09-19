#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "AnimationManager.h"

class Game
{
public:
	Game();
	~Game();

private:
	sf::RenderWindow m_window{ sf::VideoMode(600, 600), "Lonely Hero" };
	
	sf::Event m_event{};
	
	static sf::Clock clock;
	
	sf::Time m_elapsed{};

	Player m_player{};

	
};
