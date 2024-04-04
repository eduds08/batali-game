#pragma once

#include "StateContext.h"
#include <thread>
#include <memory>
#include "CharacterStatusUI.h"

#include "World.h"

class PlayingState : public StateContext
{
public:
	PlayingState(sf::RenderWindow& window, float& deltaTime, const std::string& firstCharacter, const std::string& secondCharacter);
	virtual ~PlayingState();

	virtual void update();
	virtual void render();

	//void updateCollisions();

	// Check collision with tiles around the actor's shape
	//void updateActorCollisionWithTiles(ColliderActor& actor, Ground& tile);

	// Calls knockbackMove for the attacked actor
	//void handleKnockbackMove(Character& attackingActor, Character& attackedActor, bool isUltimateActivate);

	void updateView();

	// Thread method to run all animations
	//void updateTexturesAndAnimations();

private:
	//std::vector<std::shared_ptr<Player>> m_characters{};

	std::unique_ptr<Player> player;

	//std::vector<CharacterStatusUI> m_characterStatus{};

	World m_world{};

	std::thread m_animationThread;

	// 0 -> top, 1 -> right, 2 -> bottom, 3 -> left
	std::vector<float> m_viewLimits{ 0.f, 0.f, 0.f, 0.f };

	float& m_deltaTime;

	bool m_onPause{ false };
	bool m_debugMode{ false };
};
