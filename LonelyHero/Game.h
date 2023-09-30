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
	void update();
	void render();
	void run();

	void updateCollision();

	void loadAndCreateMap(const std::string& mapFilePath);

	void updateTexturesAndAnimations();

	static bool isRunning;

private:
	sf::RenderWindow m_window{ sf::VideoMode(screenWidth, screenHeight), "Lonely Hero" };

	sf::Clock m_clock{};

	sf::Clock clock2{};
	float clock2Time{2.f};

	sf::Event m_event{};
	float m_deltaTime{};

	Player m_player{ playerSpriteWidth, playerSpriteHeight, playerSpriteScale, "playerIdle", "./_Idle.png", playerIdleAnimationFramesAmount, playerShapeWidth, playerShapeHeight, playerFirstPosition };
	std::vector<Ground> grounds{};
	
	sf::View m_view{sf::Vector2f{0.f, 0.f}, sf::Vector2f{450.f, 450.f}};

	std::thread animationThread;
	std::mutex animationMutex;
	std::thread collisionThread;

	Enemy m_enemy{ enemySpriteWidth, enemySpriteHeight, enemySpriteScale, "enemyIdle", "./_Idle2.png", enemyIdleAnimationFramesAmount, enemyShapeWidth, enemyShapeHeight, enemyFirstPosition, m_player.getPosition() };
};
