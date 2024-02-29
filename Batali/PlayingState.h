#pragma once

#include "StateContext.h"
#include "Ground.h"
#include <thread>
#include <fstream>
#include "WindHashashin.h"
#include "FireKnight.h"
#include <memory>
#include "CharacterStatusUI.h"

class PlayingState : public StateContext
{
public:
	PlayingState(sf::RenderWindow& window, float& deltaTime, bool twoPlayers, const std::string& firstCharacter, const std::string& secondCharacter);
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

	void setOnPause(bool onPause) { m_onPause = onPause; }
	bool getOnPause() { return m_onPause; }

	// Thread method to capture player's inputs
	void updatePlayerInput();

private:
	// fix bug where one press of the input pause and unpause many times in a row
	sf::Clock m_pauseClock{};
	float m_pauseDelay{};

	std::vector<std::shared_ptr<Character>> m_players{};
	std::vector<std::unique_ptr<Character>> m_bots{};

	std::vector<Ground> m_grounds{};

	std::thread animationThread;

	std::thread playerInputThread;

	float m_rightViewLimit{};
	float m_leftViewLimit{};
	float m_topViewLimit{};
	float m_bottomViewLimit{};

	float& m_deltaTime;

	bool m_onPause{ false };

	bool m_twoPlayers{};

	CharacterStatusUI fireKnightStatus{ "fireKnightLogo", "./assets/fireKnightLogo.png", m_view.getCenter() - m_view.getSize() / 2.f };
	CharacterStatusUI fireKnightStatus2{ "fireKnightLogo", "./assets/fireKnightLogo.png", m_view.getCenter() + sf::Vector2f{ m_view.getSize().x / 2.f, -m_view.getSize().y / 2.f }, false};
};
