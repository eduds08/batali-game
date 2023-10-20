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

	// Checks the collision of entity with the tiles that are inside its imaginary view.
	void updateEntityCollisionWithGrounds(MovableEntity& entity, Ground& ground);

	// Calls takeDamage and also knockbackMove for the attacked entity
	void handleEntityAttacked(SwordEntity& attackingEntity, DamageEntity& attackedEntity);
	
	void updateView();

	// Reads a .txt file to generate the tiles
	void loadAndCreateMap(const std::string& mapFilePath);

	// Thread method to run all animations
	void updateTexturesAndAnimations();

	static bool isGameRunning;

private:
	sf::RenderWindow m_window{ sf::VideoMode(screenWidth, screenHeight), "Lonely Hero" };

	sf::Event m_event{};

	sf::Clock m_deltaTimeClock{};
	float m_deltaTime{};

	Player m_player{ playerFirstPosition };
	std::vector<Enemy> enemies{};
	std::vector<Ground> grounds{};
	
	std::thread animationThread;

	sf::View m_view{sf::Vector2f{0.f, 0.f}, sf::Vector2f{viewWidth, viewHeight}};
	float m_rightViewLimit{};
	float m_leftViewLimit{};
	float m_topViewLimit{};
	float m_bottomViewLimit{};
};
