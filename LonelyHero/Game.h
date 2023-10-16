#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Ground.h"
#include <fstream>
#include <utility>
#include <vector>
#include <thread>
#include <mutex>

using namespace constants;

class Game
{
public:
	Game();
	~Game() {};

	void init();
	void run();
	void update();
	void render();

	void updateCollision();

	void updateView();

	void loadAndCreateMap(const std::string& mapFilePath);

	void updateTexturesAndAnimations();

	static bool isGameRunning;

private:
	sf::RenderWindow m_window{ sf::VideoMode(screenWidth, screenHeight), "Lonely Hero" };
	sf::View m_view{sf::Vector2f{0.f, 0.f}, sf::Vector2f{450.f, 450.f}};

	sf::Clock m_deltaTimeClock{};
	float m_deltaTime{};

	sf::Event m_event{};
	
	Player m_player{ knightSpriteWidth, knightSpriteHeight, knightSpriteScale, "playerIdle", "./assets/player/_Idle.png", knightIdleAnimationFramesAmount, "player", knightShapeWidth, knightShapeHeight, playerFirstPosition};
	std::vector<Enemy> enemies{};
	std::vector<Ground> grounds{};
	
	std::thread animationThread;

	float m_horizontalViewLimitRight{};
	float m_horizontalViewLimitLeft{};
	float m_verticalViewLimitTop{};
	float m_verticalViewLimitBottom{};
};
