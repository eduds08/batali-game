#pragma once

#include "Player.h"
#include "Enemy.h"
#include "HealthBarUI.h"
#include "Ground.h"
#include <fstream>
#include <vector>
#include <thread>

#include "MainMenu.h"

using namespace constants;

class Game
{
public:
	Game(float& deltaTime);
	~Game() { animationThread.join(); };

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

	bool isGameRunning{ true };

//private:
	//sf::RenderWindow m_window{ sf::VideoMode(screenWidth, screenHeight), "Lonely Hero" };

	HealthBarUI m_playerHealthBar{ sf::Vector2f{0.f, 0.f}, "playerHealthBar", "./assets/ui/playerHealthBar.png" };
	HealthBarUI m_enemyHealthBar{ sf::Vector2f{0.f, 0.f}, "enemyHealthBar", "./assets/ui/enemyHealthBar.png" };

	//sf::Event m_event{};

	//sf::Clock m_deltaTimeClock{};
	float& m_deltaTime;

	Player m_player{ playerFirstPosition };
	std::vector<Enemy> enemies{};
	std::vector<Ground> grounds{};
	
	std::thread animationThread;

	sf::View m_view{sf::Vector2f{0.f, 0.f}, sf::Vector2f{viewWidth, viewHeight}};
	float m_rightViewLimit{};
	float m_leftViewLimit{};
	float m_topViewLimit{};
	float m_bottomViewLimit{};


	MainMenu temporario{};
};
