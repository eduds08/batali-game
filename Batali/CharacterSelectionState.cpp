#include "CharacterSelectionState.h"

CharacterSelectionState::CharacterSelectionState(sf::RenderWindow& window, const std::string& chosenGamemode)
	: ButtonAuxState{ window }
	, m_chosenGamemode{ chosenGamemode }
{
	m_currentState = CHARACTER_SELECTION_STATE;

	m_totalCharactersAmount = static_cast<int>(m_charactersNames.size());

	// Initialize view
	m_view = m_window.getDefaultView();
	m_window.setView(m_view);

	initSmallPortraits();

	// Initialize PlayerTurn for Player 1
	m_playerTurn.setFillColor(PLAYER_1_COLOR);
	m_playerTurn.setPosition(m_buttons[0]->getSpritePosition() + sf::Vector2f{-170.f, 0.f});

	m_buttonsBackground.setSpritePosition(m_view.getCenter() + sf::Vector2f{ 0.f, 300.f });

	m_bigCharacterPortraits.emplace_back(BigCharacterPortraitUI{ m_charactersNames[0] + "Portrait", "./assets/" + m_charactersNames[0] + "/portrait.png", m_buttons.front()->getSpritePosition() + sf::Vector2f{-512.f, -64.f}, PLAYER_1_COLOR });
	m_bigCharacterPortraits.emplace_back(BigCharacterPortraitUI{ m_charactersNames[0] + "Portrait", "./assets/" + m_charactersNames[0] + "/portrait.png", m_buttons.back()->getSpritePosition() + sf::Vector2f{512.f, -64.f}, PLAYER_2_COLOR });

	// Update text above big portraits
	for (auto& playerPortraitText : m_playerPortraitsText)
	{
		playerPortraitText.setOrigin(playerPortraitText.getLocalBounds().width / 2.f, playerPortraitText.getLocalBounds().height / 2.f);

		if (playerPortraitText.getString() == "Player 1")
		{
			playerPortraitText.setFillColor(PLAYER_1_COLOR);
			playerPortraitText.setPosition(m_bigCharacterPortraits.front().getSpritePosition() - sf::Vector2f{ 0.f, m_bigCharacterPortraits.front().getSpriteSize().y * 3.f + playerPortraitText.getCharacterSize() / 2.f });
		}
		else
		{
			playerPortraitText.setString(m_chosenGamemode == "singleplayer" ? "Enemy:" : "Player 2:");
			playerPortraitText.setFillColor(PLAYER_2_COLOR);
			playerPortraitText.setPosition(m_bigCharacterPortraits.back().getSpritePosition() - sf::Vector2f{ 0.f, m_bigCharacterPortraits.back().getSpriteSize().y * 3.f + playerPortraitText.getCharacterSize() / 2.f });
		}
	}
}

void CharacterSelectionState::update()
{
	if (m_playerChoice == 1 || m_playerChoice == 2)
	{
		if (m_onHoverButton == 0)
		{
			m_bigCharacterPortraits[m_playerChoice - 1].setTexture(m_charactersNames[0] + "Portrait", "./assets/" + m_charactersNames[0] + "/portrait.png");
		}
		else if (m_onHoverButton == 1)
		{
			m_bigCharacterPortraits[m_playerChoice - 1].setTexture(m_charactersNames[1] + "Portrait", "./assets/" + m_charactersNames[1] + "/portrait.png");
		}
		else if (m_onHoverButton == 2)
		{
			m_bigCharacterPortraits[m_playerChoice - 1].setTexture(m_charactersNames[2] + "Portrait", "./assets/" + m_charactersNames[2] + "/portrait.png");
		}
	}
	else if (m_playerChoice == 3)
	{
		// Initialize "play" and "back" buttons
		m_buttons.clear();
		initTextButton("Play", m_view.getCenter() + sf::Vector2f{ -130.f, 300.f }, m_chosenGamemode == "singleplayer" ? CHARACTER_SELECTION_TO_SINGLEPLAYER : CHARACTER_SELECTION_TO_MULTIPLAYER);
		initTextButton("Back", m_view.getCenter() + sf::Vector2f{ 130.f, 300.f }, CHARACTER_SELECTION_RESET);
		++m_playerChoice;
	}

	updateButtons(false);
}

void CharacterSelectionState::render()
{
	m_window.draw(m_background.getSprite());

	if (m_playerChoice == 1 || m_playerChoice == 2)
	{
		m_window.draw(m_playerTurn);
	}

	for (auto& characterPortrait : m_bigCharacterPortraits)
	{
		characterPortrait.render(m_window);
	}

	for (auto& playerPortraitText : m_playerPortraitsText)
	{
		m_window.draw(playerPortraitText);
	}

	if (m_playerChoice > 2)
	{
		m_window.draw(m_buttonsBackground.getSprite());
	}

	renderButtons();
}

void CharacterSelectionState::initSmallPortraits()
{
	int auxPos = 0;

	// Even amount
	if (m_totalCharactersAmount % 2 == 0)
	{
		float offsetAux = (CHARACTER_SELECTION_PORTRAIT_OFFSET / 2.f) * (m_totalCharactersAmount - 1);

		for (int i = 0; i <= static_cast<int>(m_totalCharactersAmount / 2.f); ++i)
		{
			initImageButton(m_view.getCenter() + sf::Vector2f{ -static_cast<float>(CHARACTER_PORTRAIT_WIDTH) * ((m_totalCharactersAmount / 2.f) - i) + (auxPos < static_cast<int>(m_totalCharactersAmount / 2.f) ? -offsetAux : +offsetAux), -m_view.getSize().y / 4.f }, m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png");
			if (auxPos + 1 < m_totalCharactersAmount)
			{
				++auxPos;
				if (auxPos < static_cast<int>(m_totalCharactersAmount / 2.f))
					offsetAux -= 2.f * (CHARACTER_SELECTION_PORTRAIT_OFFSET / 2.f);
				else if (auxPos > static_cast<int>(m_totalCharactersAmount / 2.f))
					offsetAux += 2.f * (CHARACTER_SELECTION_PORTRAIT_OFFSET / 2.f);
			}
		}

		for (int i = 1; 2 * i < m_totalCharactersAmount; ++i)
		{
			initImageButton(m_view.getCenter() + sf::Vector2f{ static_cast<float>(CHARACTER_PORTRAIT_WIDTH)* i + (auxPos < static_cast<int>(m_totalCharactersAmount / 2.f) ? -offsetAux : +offsetAux), -m_view.getSize().y / 4.f }, m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png");
			if (auxPos + 1 < m_totalCharactersAmount)
			{
				++auxPos;
				if (auxPos < static_cast<int>(m_totalCharactersAmount / 2.f))
					offsetAux -= 2.f * (CHARACTER_SELECTION_PORTRAIT_OFFSET / 2.f);
				else if (auxPos > static_cast<int>(m_totalCharactersAmount / 2.f))
					offsetAux += 2.f * (CHARACTER_SELECTION_PORTRAIT_OFFSET / 2.f);
			}
		}
	}
	// Odd amount
	else
	{
		float offsetAux = (CHARACTER_SELECTION_PORTRAIT_OFFSET / 2.f) * (static_cast<int>(m_totalCharactersAmount / 2) * 2.f);

		for (int i = 0; i < m_totalCharactersAmount; i += 2)
		{
			initImageButton(m_view.getCenter() + sf::Vector2f{ -static_cast<float>(CHARACTER_PORTRAIT_WIDTH) * ((m_totalCharactersAmount - i) / 2.f) + (auxPos < static_cast<int>(m_totalCharactersAmount / 2.f) ? -offsetAux : +offsetAux), -m_view.getSize().y / 4.f }, m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png");
			if (auxPos + 1 < m_totalCharactersAmount)
			{
				++auxPos;
				if (auxPos > static_cast<int>(m_totalCharactersAmount / 2.f))
					offsetAux += 2.f * (CHARACTER_SELECTION_PORTRAIT_OFFSET / 2.f);
				else
					offsetAux -= 2.f * (CHARACTER_SELECTION_PORTRAIT_OFFSET / 2.f);
			}
		}

		for (int i = m_totalCharactersAmount - 1; i > 0; i -= 2)
		{
			initImageButton(m_view.getCenter() + sf::Vector2f{ static_cast<float>(CHARACTER_PORTRAIT_WIDTH)* ((m_totalCharactersAmount - i) / 2.f) + (auxPos < static_cast<int>(m_totalCharactersAmount / 2.f) ? -offsetAux : +offsetAux), -m_view.getSize().y / 4.f }, m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png");
			if (auxPos + 1 < m_totalCharactersAmount)
			{
				++auxPos;
				if (auxPos > static_cast<int>(m_totalCharactersAmount / 2.f))
					offsetAux += 2.f * 5.f;
				else
					offsetAux -= 2.f * 5.f;
			}
		}
	}
}

void CharacterSelectionState::selectCharacter()
{
	m_chosenCharacters.emplace_back(m_charactersNames[m_onHoverButton]);

	// Updates the display to indicates that Player 2 (or Enemy) is selecting character
	if (m_playerChoice == 1)
	{
		m_playerTurn.setString(m_chosenGamemode == "singleplayer" ? "Enemy:" : "Player 2:");
		m_playerTurn.setFillColor(PLAYER_2_COLOR);
		m_playerTurn.setPosition(m_buttons[0]->getSpritePosition() + sf::Vector2f{-170.f, 0.f});
	}

	++m_playerChoice;
	m_onHoverButton = 0;
}
