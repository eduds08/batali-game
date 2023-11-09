#pragma once

#include "StateContext.h"
#include "Player.h"
#include "Enemy.h"
#include "Ground.h"
#include "HealthBarUI.h"
#include <thread>
#include <fstream>

class PlayingState : public StateContext
{
public:
	PlayingState(sf::RenderWindow& window, float& deltaTime);
	virtual ~PlayingState();

	virtual void update();
	virtual void render();

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

	// Flag to control the animation thread
	void setOnPlayingState(bool onPlayingState) { m_onPlayingState = onPlayingState; }

	void setOnPause(bool onPause) { m_onPause = onPause; }
	bool getOnPause() { return m_onPause; }

private:
	

	// fix bug where one press of the input pause and unpause many times in a row
	sf::Clock m_pauseClock{};
	float m_pauseDelay{};

	Player m_player{ playerFirstPosition };
	std::vector<Enemy> enemies{};
	std::vector<Ground> grounds{};

	HealthBarUI m_playerHealthBar{ sf::Vector2f{0.f, 0.f}, "playerHealthBar", "./assets/ui/playerHealthBar.png", &m_player.getHp() };
	HealthBarUI m_enemyHealthBar{ sf::Vector2f{0.f, 0.f}, "enemyHealthBar", "./assets/ui/enemyHealthBar.png", &enemies[0].getHp() };
	
	std::thread animationThread;

	float m_rightViewLimit{};
	float m_leftViewLimit{};
	float m_topViewLimit{};
	float m_bottomViewLimit{};

	bool m_onPlayingState{ true };

	float& m_deltaTime;

	bool m_onPause{ false };
};
