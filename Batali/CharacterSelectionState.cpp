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

	//initSmallPortraits();

	int auxPos = 0;

	// Even amount
	if (m_totalCharactersAmount % 2 == 0)
	{
		for (int i = 0; i <= static_cast<int>(m_totalCharactersAmount / 2.f); ++i)
		{
			m_smallCp.emplace_back(ImageButtonUI{ m_view.getCenter() + sf::Vector2f{-static_cast<float>(CHARACTER_PORTRAIT_WIDTH) * ((m_totalCharactersAmount / 2.f) - i), 400.f}, m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png" });
			if (auxPos + 1 < m_totalCharactersAmount)
			{
				++auxPos;
			}
		}

		for (int i = 1; 2 * i < m_totalCharactersAmount; ++i)
		{
			m_smallCp.emplace_back(ImageButtonUI{ m_view.getCenter() + sf::Vector2f{static_cast<float>(CHARACTER_PORTRAIT_WIDTH)* i, 400.f}, m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png" });
			if (auxPos + 1 < m_totalCharactersAmount)
			{
				++auxPos;
			}
		}
	}
	// Odd amount
	else
	{
		for (int i = 0; i < m_totalCharactersAmount; i += 2)
		{
			m_smallCp.emplace_back(ImageButtonUI{ m_view.getCenter() + sf::Vector2f{-static_cast<float>(CHARACTER_PORTRAIT_WIDTH) * ((m_totalCharactersAmount - i) / 2.f), 400.f}, m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png" });
			if (auxPos + 1 < m_totalCharactersAmount)
			{
				++auxPos;
			}
		}

		for (int i = m_totalCharactersAmount - 1; i > 0; i -= 2)
		{
			m_smallCp.emplace_back(ImageButtonUI{ m_view.getCenter() + sf::Vector2f{static_cast<float>(CHARACTER_PORTRAIT_WIDTH)* ((m_totalCharactersAmount - i) / 2.f), 400.f}, m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png" });
			if (auxPos + 1 < m_totalCharactersAmount)
			{
				++auxPos;
			}
		}
	}

	// Initialize PlayerTurn for Player 1
	m_playerTurn.setFillColor(PLAYER_1_COLOR);
	//m_playerTurn.setPosition(m_smallCharacterPortraits[0].getSpritePosition() + sf::Vector2f{-170.f, 0.f});
	m_playerTurn.setPosition(m_smallCp[0].getSpritePosition() + sf::Vector2f{-170.f, 0.f});

	// Initialize "play" and "back" buttons
	initTextButton("Play", m_view.getCenter() + sf::Vector2f{ -130.f, 300.f }, m_chosenGamemode == "singleplayer" ? CHARACTER_SELECTION_TO_SINGLEPLAYER : CHARACTER_SELECTION_TO_MULTIPLAYER);
	initTextButton("Back", m_view.getCenter() + sf::Vector2f{ 130.f, 300.f }, CHARACTER_SELECTION_RESET);

	m_buttonsBackground.setSpritePosition(m_view.getCenter() + sf::Vector2f{ 0.f, 300.f });

	/*m_bigCharacterPortraits.emplace_back(BigCharacterPortraitUI{ m_charactersNames[0] + "Portrait", "./assets/" + m_charactersNames[0] + "/portrait.png", m_smallCharacterPortraits.front().getSpritePosition() + sf::Vector2f{-512.f, -64.f}, PLAYER_1_COLOR});
	m_bigCharacterPortraits.emplace_back(BigCharacterPortraitUI{ m_charactersNames[0] + "Portrait", "./assets/" + m_charactersNames[0] + "/portrait.png", m_smallCharacterPortraits.back().getSpritePosition() + sf::Vector2f{512.f, -64.f}, PLAYER_2_COLOR});*/

	m_bigCharacterPortraits.emplace_back(BigCharacterPortraitUI{ m_charactersNames[0] + "Portrait", "./assets/" + m_charactersNames[0] + "/portrait.png", m_smallCp.front().getSpritePosition() + sf::Vector2f{-512.f, -64.f}, PLAYER_1_COLOR });
	m_bigCharacterPortraits.emplace_back(BigCharacterPortraitUI{ m_charactersNames[0] + "Portrait", "./assets/" + m_charactersNames[0] + "/portrait.png", m_smallCp.back().getSpritePosition() + sf::Vector2f{512.f, -64.f}, PLAYER_2_COLOR });

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
		if (m_onHoverCharacterButton == 0)
		{
			m_bigCharacterPortraits[m_playerChoice - 1].setTexture(m_charactersNames[0] + "Portrait", "./assets/" + m_charactersNames[0] + "/portrait.png");
		}
		else if (m_onHoverCharacterButton == 1)
		{
			m_bigCharacterPortraits[m_playerChoice - 1].setTexture(m_charactersNames[1] + "Portrait", "./assets/" + m_charactersNames[1] + "/portrait.png");
		}
		else if (m_onHoverCharacterButton == 2)
		{
			m_bigCharacterPortraits[m_playerChoice - 1].setTexture(m_charactersNames[2] + "Portrait", "./assets/" + m_charactersNames[2] + "/portrait.png");
		}

		updateCharacterSelectionButtons();
	}
	else
	{
		updateButtons(false);
	}
}

void CharacterSelectionState::render()
{
	m_window.draw(m_background.getSprite());

	if (m_playerChoice == 1 || m_playerChoice == 2)
	{
		/*for (auto& characterPortrait : m_smallCharacterPortraits)
		{
			characterPortrait.render(m_window);
		}*/

		for (auto& characterPortrait : m_smallCp)
		{
			characterPortrait.render(m_window);
		}

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
		renderButtons();
	}
}

void CharacterSelectionState::initSmallPortraits()
{
	int auxPos = 0;

	// Even amount
	if (m_totalCharactersAmount % 2 == 0)
	{
		for (int i = 0; i <= static_cast<int>(m_totalCharactersAmount / 2.f); ++i)
		{
			//m_smallCharacterPortraits.emplace_back(SmallCharacterPortraitUI{ m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png", m_view.getCenter() + sf::Vector2f{-static_cast<float>(CHARACTER_PORTRAIT_WIDTH) * ((m_totalCharactersAmount / 2.f) - i), 400.f} });
			m_smallCp.emplace_back(ImageButtonUI{ m_view.getCenter() + sf::Vector2f{-static_cast<float>(CHARACTER_PORTRAIT_WIDTH) * ((m_totalCharactersAmount / 2.f) - i), 400.f}, m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png" });
			if (auxPos + 1 < m_totalCharactersAmount)
			{
				++auxPos;
			}
		}

		for (int i = 1; 2 * i < m_totalCharactersAmount; ++i)
		{
			//m_smallCharacterPortraits.emplace_back(SmallCharacterPortraitUI{ m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png", m_view.getCenter() + sf::Vector2f{static_cast<float>(CHARACTER_PORTRAIT_WIDTH)* i, 400.f} });
			m_smallCp.emplace_back(ImageButtonUI{ m_view.getCenter() + sf::Vector2f{static_cast<float>(CHARACTER_PORTRAIT_WIDTH)* i, 400.f}, m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png" });
			if (auxPos + 1 < m_totalCharactersAmount)
			{
				++auxPos;
			}
		}
	}
	// Odd amount
	else
	{
		for (int i = 0; i < m_totalCharactersAmount; i += 2)
		{
			//m_smallCharacterPortraits.emplace_back(SmallCharacterPortraitUI{ m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png", m_view.getCenter() + sf::Vector2f{-static_cast<float>(CHARACTER_PORTRAIT_WIDTH) * ((m_totalCharactersAmount - i) / 2.f), 400.f} });
			m_smallCp.emplace_back(ImageButtonUI{ m_view.getCenter() + sf::Vector2f{-static_cast<float>(CHARACTER_PORTRAIT_WIDTH) * ((m_totalCharactersAmount - i) / 2.f), 400.f}, m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png" });
			if (auxPos + 1 < m_totalCharactersAmount)
			{
				++auxPos;
			}
		}

		for (int i = m_totalCharactersAmount - 1; i > 0; i -= 2)
		{
			//m_smallCharacterPortraits.emplace_back(SmallCharacterPortraitUI{ m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png", m_view.getCenter() + sf::Vector2f{static_cast<float>(CHARACTER_PORTRAIT_WIDTH)* ((m_totalCharactersAmount - i) / 2.f), 400.f} });
			m_smallCp.emplace_back(ImageButtonUI{ m_view.getCenter() + sf::Vector2f{static_cast<float>(CHARACTER_PORTRAIT_WIDTH)* ((m_totalCharactersAmount - i) / 2.f), 400.f}, m_charactersNames[auxPos] + "Portrait", "./assets/" + m_charactersNames[auxPos] + "/portrait.png" });
			if (auxPos + 1 < m_totalCharactersAmount)
			{
				++auxPos;
			}
		}
	}
}

void CharacterSelectionState::updateCharacterSelectionButtons()
{
	// Move right
	if (m_pressedKey == sf::Keyboard::Scancode::Right)
	{
		/*if (m_onHoverCharacterButton < m_smallCharacterPortraits.size() - 1)
		{
			++m_onHoverCharacterButton;
		}*/
		if (m_onHoverCharacterButton < m_smallCp.size() - 1)
		{
			++m_onHoverCharacterButton;
		}
	}
	// Move left
	else if (m_pressedKey == sf::Keyboard::Scancode::Left)
	{
		if (m_onHoverCharacterButton > 0)
		{
			--m_onHoverCharacterButton;
		}
	}

	// Upate the visual design of the characterPortrait (according to its state -> onHover OR not onHover)
	/*for (size_t i = 0; i < m_smallCharacterPortraits.size(); ++i)
	{
		m_smallCharacterPortraits[i].update(i == m_onHoverCharacterButton, m_playerChoice == 1 ? PLAYER_1_COLOR : PLAYER_2_COLOR);
	}*/

	for (size_t i = 0; i < m_smallCp.size(); ++i)
	{
		m_smallCp[i].update(i == m_onHoverCharacterButton);
	}

	// Select character
	if (m_pressedKey == sf::Keyboard::Scancode::Enter)
	{
		selectCharacter();
	}

	m_pressedKey = sf::Keyboard::Scancode::Unknown;
}

void CharacterSelectionState::selectCharacter()
{
	m_chosenCharacters.emplace_back(m_charactersNames[m_onHoverCharacterButton]);

	// Updates the display to indicates that Player 2 (or Enemy) is selecting character
	if (m_playerChoice == 1)
	{
		m_playerTurn.setString(m_chosenGamemode == "singleplayer" ? "Enemy:" : "Player 2:");
		m_playerTurn.setFillColor(PLAYER_2_COLOR);
		//m_playerTurn.setPosition(m_smallCharacterPortraits[0].getSpritePosition() + sf::Vector2f{-170.f, 0.f});
		m_playerTurn.setPosition(m_smallCp[0].getSpritePosition() + sf::Vector2f{-170.f, 0.f});
	}

	++m_playerChoice;
	m_onHoverCharacterButton = 0;
}
