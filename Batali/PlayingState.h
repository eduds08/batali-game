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

	void updateView();

private:
	//std::vector<CharacterStatusUI> m_characterStatus{};

	World m_world{};

	std::thread m_animationThread;

	// 0 -> top, 1 -> right, 2 -> bottom, 3 -> left
	std::vector<float> m_viewLimits{ 0.f, 0.f, 0.f, 0.f };

	float& m_deltaTime;

	bool m_onPause{ false };
	bool m_debugMode{ false };
};
