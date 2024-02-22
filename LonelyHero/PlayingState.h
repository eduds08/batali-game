#pragma once

#include "StateContext.h"
#include "Ground.h"
#include "HealthBarUI.h"
#include <thread>
#include <fstream>
#include "WindHashashin.h"
#include "FireKnight.h"

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

	/*std::vector<Player> players{Player{ playerFirstPosition, "FIRE_KNIGHT", 1 }, Player{ playerFirstPosition, "WIND_HASHASHIN", 2 }};
	std::vector<Enemy> enemies{ Enemy{ enemyFirstPosition, players[0].getPosition() } };*/


	std::vector<FireKnight> players{FireKnight{ playerFirstPosition}, FireKnight{ playerFirstPosition, 2 }};

	std::vector<WindHashashin> enemies{WindHashashin{ playerFirstPosition}, WindHashashin{ playerFirstPosition, 2 }};


	std::vector<Ground> grounds{};

	//sf::Vector2f firstPosition, bool isBot=false, int playerNumber=0, sf::Vector2f* playerPosition=nullptr

	HealthBarUI m_playerHealthBar{ sf::Vector2f{0.f, 0.f}, "playerHealthBar", "./assets/ui/playerHealthBar.png", &players[0].getHp()};

	HealthBarUI m_enemyHealthBar{ sf::Vector2f{0.f, 0.f}, "enemyHealthBar", "./assets/ui/enemyHealthBar.png", &enemies[0].getHp() };
	HealthBarUI m_player2HealthBar{ sf::Vector2f{0.f, 0.f}, "enemyHealthBar", "./assets/ui/enemyHealthBar.png", &players[1].getHp() };

	std::thread animationThread;

	float m_rightViewLimit{};
	float m_leftViewLimit{};
	float m_topViewLimit{};
	float m_bottomViewLimit{};

	bool m_onPlayingState{ true };

	float& m_deltaTime;

	bool m_onPause{ false };

	bool twoPlayers{ true };
};
