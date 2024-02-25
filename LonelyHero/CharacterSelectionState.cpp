#include "CharacterSelectionState.h"

CharacterSelectionState::CharacterSelectionState(sf::RenderWindow& window, const std::string& chosenGamemode)
	: ButtonAuxState{ window }
	, m_chosenGamemode{ chosenGamemode }
{
	m_currentState = constants::characterSelectionState;

	// Initialize view
	m_view = m_window.getDefaultView();
	m_view.setCenter(0.f, 0.f);
	m_window.setView(m_view);

	// Initialize small portraits
	m_smallCharacterPortraits.emplace_back(CharacterPortraitUI{ "fireKnightPortrait", "./assets/portrait_fire_knight.png", m_view.getCenter() - sf::Vector2f{50.f, -400.f}, false });
	m_smallCharacterPortraits.emplace_back(CharacterPortraitUI{ "windHashashinPortrait", "./assets/portrait_wind_hashashin.png", m_view.getCenter() + sf::Vector2f{50.f, 400.f}, false });

	// Initialize PlayerTurn for Player 1
	m_playerTurn.setOrigin(m_playerTurn.getLocalBounds().width / 2.f, m_playerTurn.getLocalBounds().height / 2.f);
	m_playerTurn.setFillColor(sf::Color::Magenta);
	m_playerTurn.setPosition(m_view.getCenter() - sf::Vector2f{ 170.f, -400.f });

	// Update text above big portraits
	for (auto& playerPortraitText : m_playerPortraitsText)
	{
		playerPortraitText.setOrigin(playerPortraitText.getLocalBounds().width / 2.f, playerPortraitText.getLocalBounds().height / 2.f);

		if (playerPortraitText.getString() == "Player 1")
		{
			playerPortraitText.setFillColor(sf::Color::Magenta);
			playerPortraitText.setPosition(m_view.getCenter() - sf::Vector2f{ 250.f, 180.f });
		}
		else
		{
			playerPortraitText.setString(m_chosenGamemode == "singleplayer" ? "Enemy:" : "Player 2:");
			playerPortraitText.setFillColor(sf::Color::Yellow);
			playerPortraitText.setPosition(m_view.getCenter() + sf::Vector2f{ 250.f, -180.f });
		}
	}

	// Initialize big portrait borders
	initBigPortraitBorders(1);
	initBigPortraitBorders(2);

	// Initialize "play" and "back" buttons
	initButton("Play", m_view.getCenter() + sf::Vector2f{ -150.f, 270.f }, m_chosenGamemode == "singleplayer" ? constants::characterSelectionToSingleplayerTransition : constants::characterSelectionToMultiplayerTransition);
	initButton("Back", m_view.getCenter() + sf::Vector2f{ 150.f, 270.f }, constants::characterSelectionReset);
}

void CharacterSelectionState::update()
{
	if (m_playerChoice == 1 || m_playerChoice == 2)
	{
		updateCharacterSelectionButtons();
	}
	else
	{
		updateButtons(false);
	}
}

void CharacterSelectionState::render()
{
	if (m_playerChoice == 1 || m_playerChoice == 2)
	{
		for (auto& characterPortrait : m_smallCharacterPortraits)
		{
			m_window.draw(characterPortrait.m_portraitBorder);
			m_window.draw(characterPortrait.getSprite());
		}

		m_window.draw(m_playerTurn);
	}

	for (auto& characterPortrait : m_bigCharacterPortraits)
	{
		m_window.draw(characterPortrait.getSprite());
	}

	for (auto& playerPortraitText : m_playerPortraitsText)
	{
		m_window.draw(playerPortraitText);
	}

	for (auto& portraitBorder : m_bigPortraitsBorder)
	{
		m_window.draw(portraitBorder);
	}

	if (m_playerChoice > 2)
	{
		renderButtons();
	}
}

void CharacterSelectionState::updateCharacterSelectionButtons()
{
	delayTime = delayClock.getElapsedTime().asSeconds();

	// Move right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right) && delayTime > 0.18f)
	{
		if (m_onHoverCharacterButton < m_smallCharacterPortraits.size() - 1)
		{
			++m_onHoverCharacterButton;

			delayClock.restart();
		}
	}
	// Move left
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left) && delayTime > 0.18f)
	{
		if (m_onHoverCharacterButton > 0)
		{
			--m_onHoverCharacterButton;

			delayClock.restart();
		}
	}

	// Upate the visual design of the characterPortrait (according to its state -> onHover OR not onHover)
	for (size_t i = 0; i < m_smallCharacterPortraits.size(); ++i)
	{
		m_smallCharacterPortraits[i].update(i == m_onHoverCharacterButton, m_playerChoice == 1 ? sf::Color::Magenta : sf::Color::Yellow);
	}

	// Select character
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter) && delayTime > 0.18f)
	{
		selectCharacter();
		delayClock.restart();
	}
}

void CharacterSelectionState::selectCharacter()
{
	sf::Vector2f portraitPosition = m_view.getCenter() + (m_playerChoice == 1 ? sf::Vector2f{ -250.f, 0.f } : sf::Vector2f{ 250.f, 0.f });

	// Select fireKnight
	if (m_onHoverCharacterButton == 0)
	{
		m_bigCharacterPortraits.emplace_back(CharacterPortraitUI{ "fireKnightPortrait", "./assets/portrait_fire_knight.png", portraitPosition, true });
		m_chosenCharacters.emplace_back("fire_knight");
	}
	// Select windHashashin
	else if (m_onHoverCharacterButton == 1)
	{
		m_bigCharacterPortraits.emplace_back(CharacterPortraitUI{ "windHashashinPortrait", "./assets/portrait_wind_hashashin.png", portraitPosition, true });
		m_chosenCharacters.emplace_back("wind_hashashin");
	}

	// Updates the display to indicates that Player 2 (or Enemy) is selecting character
	if (m_playerChoice == 1)
	{
		m_playerTurn.setString(m_chosenGamemode == "singleplayer" ? "Enemy:" : "Player 2:");
		m_playerTurn.setFillColor(sf::Color::Yellow);
		m_playerTurn.setPosition(m_view.getCenter() - sf::Vector2f{ m_chosenGamemode == "singleplayer" ? 140.f : 170.f, -400.f });
	}

	++m_playerChoice;
}

void CharacterSelectionState::initBigPortraitBorders(int playerNumber)
{
	sf::RectangleShape portraitBorder{ sf::Vector2f{constants::characterPortraitSpriteWidth * 5.f, constants::characterPortraitSpriteHeight * 5.f} };

	portraitBorder.setOutlineThickness(1.f);
	portraitBorder.setOrigin(portraitBorder.getSize() / 2.f);
	portraitBorder.setOutlineColor(playerNumber == 1 ? sf::Color::Magenta : sf::Color::Yellow);
	portraitBorder.setPosition(m_view.getCenter() - (playerNumber == 1 ? sf::Vector2f{ 250.f, 0.f } : sf::Vector2f{ -250.f, 0.f }) );
	portraitBorder.setFillColor(sf::Color::Transparent);

	m_bigPortraitsBorder.emplace_back(portraitBorder);
}
