#pragma once

#include "StateContext.h"
#include "Ground.h"
#include "HealthBarUI.h"
#include <thread>
#include <fstream>
#include "WindHashashin.h"
#include "FireKnight.h"
#include <memory>

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

	sf::Texture temp{};
	sf::Sprite wallpaper{};

private:
	// fix bug where one press of the input pause and unpause many times in a row
	sf::Clock m_pauseClock{};
	float m_pauseDelay{};

	std::vector<std::unique_ptr<Character>> m_players{};
	std::vector<std::unique_ptr<Character>> m_bots{};

	std::vector<Ground> m_grounds{};

	HealthBarUI m_playerHealthBar{ "playerHealthBar", "./assets/ui/playerHealthBar.png" };
	HealthBarUI m_enemyHealthBar{ "enemyHealthBar", "./assets/ui/enemyHealthBar.png" };
	HealthBarUI m_player2HealthBar{ "enemyHealthBar", "./assets/ui/enemyHealthBar.png" };

	std::thread animationThread;

	float m_rightViewLimit{};
	float m_leftViewLimit{};
	float m_topViewLimit{};
	float m_bottomViewLimit{};

	bool m_onPlayingState{ true };

	float& m_deltaTime;

	bool m_onPause{ false };

	bool m_twoPlayers{ true };
};
