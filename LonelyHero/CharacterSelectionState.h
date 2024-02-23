#pragma once

#include "StateContext.h"
#include "CharacterPortraitUI.h"

class CharacterSelectionState : public StateContext
{
public:
	CharacterSelectionState(sf::RenderWindow& window);
	virtual ~CharacterSelectionState() = default;

	virtual void update();
	virtual void render();

	void selectCharacter();
private:
	std::vector<CharacterPortraitUI> m_bigCharacterPortraits{};
	std::vector<CharacterPortraitUI> m_smallCharacterPortraits{};

	sf::Clock delayClock{};
	float delayTime{};

	size_t m_onHoverButton{ 0 };

	int m_playerChoice{ 1 };
};
