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
	sf::RenderWindow m_window{ sf::VideoMode(constants::screenWidth, constants::screenHeight), "Lonely Hero" };

	sf::Clock m_clock{};
	sf::Event m_event{};
	float m_deltaTime{};

	Player m_player{ constants::playerSpriteWidth, constants::playerSpriteHeight, constants::playerShapeWidth, constants::playerShapeHeight, constants::playerIdleAnimationFramesAmount, constants::playerSwitchAnimationTime };
	std::vector<Ground> grounds{};
};
