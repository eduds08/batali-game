#pragma once

#include "ButtonAuxState.h"
#include "CharacterPortraitUI.h"
#include "ButtonUI.h"

class CharacterSelectionState : public ButtonAuxState
{
public:
	CharacterSelectionState(sf::RenderWindow& window, const std::string& chosenGamemode);
	virtual ~CharacterSelectionState() = default;

	virtual void update();
	virtual void render();

	// Same logic of updateButtons()
	void updateCharacterSelectionButtons();

	void selectCharacter();

	void initBigPortraitBorders(int playerNumber);

	std::vector<std::string> m_chosenCharacters{};

	std::string getChosenGamemode() { return m_chosenGamemode; }

private:
	std::vector<CharacterPortraitUI> m_bigCharacterPortraits{};
	std::vector<CharacterPortraitUI> m_smallCharacterPortraits{};

	// Indicates which player is selecting the character
	sf::Text m_playerTurn{ "Player 1:", m_font };

	// Text above the big player portrait
	std::vector<sf::Text> m_playerPortraitsText{ sf::Text{"Player 1", m_font}, sf::Text{"Player 2", m_font} };

	size_t m_onHoverCharacterButton{ 0 };

	// Player 1 or player 2
	int m_playerChoice{ 1 };

	// Outline border of the big portrait
	std::vector<sf::RectangleShape> m_bigPortraitsBorder{};

	// Singleplayer or multiplayer
	const std::string m_chosenGamemode{};
};
