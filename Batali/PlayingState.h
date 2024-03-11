#pragma once

#include "StateContext.h"
#include "Ground.h"
#include <thread>
#include <fstream>
#include "WindHashashin.h"
#include "FireKnight.h"
#include <memory>
#include "Boxer.h"
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
	void updateEntityCollisionWithGrounds(WalkingEntity& entity, Ground& ground);

	// Calls takeDamage and also knockbackMove for the attacked entity
	void handleEntityAttacked(SwordEntity& attackingEntity, DamageEntity& attackedEntity, bool isUltimateActivate = false);

	void updateView();

	// Reads a .txt file to generate the tiles
	void loadAndCreateMap(const std::string& mapFilePath);

	// Thread method to run all animations
	void updateTexturesAndAnimations();

	void setOnPause(bool onPause) { m_onPause = onPause; }
	bool getOnPause() { return m_onPause; }

	// Thread method to capture player's inputs
	void updatePlayer1Input();
	void updatePlayer2Input();

private:
	std::vector<std::shared_ptr<Character>> m_characters{};
	std::vector<CharacterStatusUI> m_characterStatus{};
	std::vector<Ground> m_grounds{};

	std::thread m_animationThread;

	std::thread m_player1InputThread;
	std::thread m_player2InputThread;

	float m_rightViewLimit{};
	float m_leftViewLimit{};
	float m_topViewLimit{};
	float m_bottomViewLimit{};

	float& m_deltaTime;

	bool m_onPause{ false };

	bool m_twoPlayers{};

	bool m_debugMode{ false };
};
