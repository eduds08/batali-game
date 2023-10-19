#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Ground.h"
#include <fstream>
#include <vector>
#include <thread>

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
	void updateCollisionWithGrounds();

	void updateView();

	void loadAndCreateMap(const std::string& mapFilePath);

	void updateTexturesAndAnimations();

	static bool isGameRunning;

private:
	sf::RenderWindow m_window{ sf::VideoMode(screenWidth, screenHeight), "Lonely Hero" };
	sf::View m_view{sf::Vector2f{0.f, 0.f}, sf::Vector2f{viewWidth, viewHeight}};

	sf::Clock m_deltaTimeClock{};
	float m_deltaTime{};

	sf::Event m_event{};
	
	Player m_player{ playerFirstPosition };
	std::vector<Enemy> enemies{};
	std::vector<Ground> grounds{};
	
	std::thread animationThread;

	float m_rightViewLimit{};
	float m_leftViewLimit{};
	float m_topViewLimit{};
	float m_bottomViewLimit{};
};
