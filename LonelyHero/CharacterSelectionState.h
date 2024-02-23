#pragma once

#include "StateContext.h"
#include "CharacterPortraitUI.h"
#include "ButtonUI.h"

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

	sf::Text m_playerTurn{ "Player 1:", m_font };

	ButtonUI m_playButton{ "button", "./assets/ui/button.png", m_view.getCenter() + sf::Vector2f{0.f, 100.f} };
	sf::Text m_playButtonText{ "Play", m_font };

	ButtonUI m_backButton{ "button", "./assets/ui/button.png", m_view.getCenter() + sf::Vector2f{0.f, 100.f} };
	sf::Text m_backButtonText{ "Back", m_font };

	std::vector<sf::Text> m_playerPortraitsText{ sf::Text{"Player 1", m_font}, sf::Text{"Player 2", m_font} };

	sf::Clock delayClock{};
	float delayTime{};

	size_t m_onHoverButton{ 0 };

	int m_playerChoice{ 1 };

	std::vector<sf::RectangleShape> m_portraitsBorder{};
};
