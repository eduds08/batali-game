#pragma once

#include "StateContext.h"
#include "CharacterPortraitUI.h"
#include "ButtonUI.h"

class CharacterSelectionState : public StateContext
{
public:
	CharacterSelectionState(sf::RenderWindow& window, const std::string& chosenGamemode);
	virtual ~CharacterSelectionState() = default;

	virtual void update();
	virtual void render();

	void updateCharacterSelectionButtons(float& delayTime);
	void updateButtonsAfterSelection(float& delayTime);

	void initButton(const std::string& text, sf::Vector2f position);

	// Called when user press enter on a button. It checks which button was pressed and then changes the current state according to it
	void pressButton();
	void selectCharacter();

	std::vector<std::string> chosenCharacters{};

private:
	std::vector<CharacterPortraitUI> m_bigCharacterPortraits{};
	std::vector<CharacterPortraitUI> m_smallCharacterPortraits{};

	sf::Text m_playerTurn{ "Player 1:", m_font };

	std::vector<ButtonUI> m_buttons{};
	std::vector<sf::Text> m_buttonsTexts{};

	std::vector<sf::Text> m_playerPortraitsText{ sf::Text{"Player 1", m_font}, sf::Text{"Player 2", m_font} };

	sf::Clock delayClock{};
	float delayTime{};

	size_t m_onHoverCharacterButton{ 0 };
	size_t m_onHoverButton{ 0 };

	int m_playerChoice{ 1 };

	std::vector<sf::RectangleShape> m_portraitsBorder{};

	std::string m_chosenGamemode{};
};
