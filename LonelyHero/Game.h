#pragma once

#include <vector>
#include "Player.h"
#include "Ground.h"
#include <fstream>
#include <utility>
#include "Enemy.h"
#include <thread>
#include <mutex>

using namespace constants;

class Game
{
public:
	Game();
	~Game();

	void init();
	void run();
	void update();
	void render();
	

	void updateCollision();

	void loadAndCreateMap(const std::string& mapFilePath);

	void updateTexturesAndAnimations();

	static bool isRunning;

private:
	sf::RenderWindow m_window{ sf::VideoMode(screenWidth, screenHeight), "Lonely Hero" };
	sf::View m_view{sf::Vector2f{0.f, 0.f}, sf::Vector2f{450.f, 450.f}};

	sf::Clock m_clock{};
	float m_deltaTime{};

	sf::Event m_event{};
	
	Player m_player{ knightSpriteWidth, knightSpriteHeight, knightSpriteScale, "playerIdle", "./assets/player/_Idle.png", knightIdleAnimationFramesAmount, knightShapeWidth, knightShapeHeight, playerFirstPosition };
	Enemy m_enemy{ knightSpriteWidth, knightSpriteHeight, knightSpriteScale, "enemyIdle", "./assets/enemy/_Idle2.png", knightIdleAnimationFramesAmount, knightShapeWidth, knightShapeHeight, enemyFirstPosition, m_player.getPosition() };
	std::vector<Ground> grounds{};
	
	std::thread animationThread;
};
