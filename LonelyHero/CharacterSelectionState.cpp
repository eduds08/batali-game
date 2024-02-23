#include "CharacterSelectionState.h"

CharacterSelectionState::CharacterSelectionState(sf::RenderWindow& window) 
	: StateContext{ window }
{
	m_currentState = constants::characterSelectionState;

	m_view = m_window.getDefaultView();
	m_view.setCenter(0.f, 0.f);
	m_window.setView(m_view);

	m_smallCharacterPortraits.emplace_back(CharacterPortraitUI{ "fireKnightPortrait", "./assets/portrait_fire_knight.png", m_view.getCenter() - sf::Vector2f{50.f, -400.f}, 1.f });
	m_smallCharacterPortraits.emplace_back(CharacterPortraitUI{ "windHashashinPortrait", "./assets/portrait_wind_hashashin.png", m_view.getCenter() + sf::Vector2f{50.f, 400.f}, 1.f });

	m_playerTurn.setOrigin(m_playerTurn.getLocalBounds().width / 2.f, m_playerTurn.getLocalBounds().height / 2.f);
	m_playerTurn.setFillColor(sf::Color::Magenta);
	m_playerTurn.setPosition(m_view.getCenter() - sf::Vector2f{ 170.f, -400.f });

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
			playerPortraitText.setFillColor(sf::Color::Yellow);
			playerPortraitText.setPosition(m_view.getCenter() + sf::Vector2f{ 250.f, -180.f });
		}
	}

	sf::RectangleShape portraitBorderPlayer1{ sf::Vector2f{constants::characterPortraitSpriteWidth * 5.f, constants::characterPortraitSpriteHeight * 5.f} };
	sf::RectangleShape portraitBorderPlayer2{ sf::Vector2f{constants::characterPortraitSpriteWidth * 5.f, constants::characterPortraitSpriteHeight * 5.f} };

	portraitBorderPlayer1.setOutlineThickness(1.f);
	portraitBorderPlayer1.setOutlineColor(sf::Color::Magenta);
	portraitBorderPlayer1.setOrigin(portraitBorderPlayer1.getSize() / 2.f);
	portraitBorderPlayer1.setPosition(m_view.getCenter() - sf::Vector2f{ 250.f, 0.f });
	portraitBorderPlayer1.setFillColor(sf::Color::Transparent);

	portraitBorderPlayer2.setOutlineThickness(1.f);
	portraitBorderPlayer2.setOutlineColor(sf::Color::Yellow);
	portraitBorderPlayer2.setOrigin(portraitBorderPlayer2.getSize() / 2.f);
	portraitBorderPlayer2.setPosition(m_view.getCenter() + sf::Vector2f{ 250.f, 0.f });
	portraitBorderPlayer2.setFillColor(sf::Color::Transparent);

	m_portraitsBorder.emplace_back(portraitBorderPlayer1);
	m_portraitsBorder.emplace_back(portraitBorderPlayer2);

	m_playButton.setPosition(m_view.getCenter() + sf::Vector2f{ -150.f, 270.f });

	m_playButtonText.setOrigin(m_playButtonText.getLocalBounds().width / 2.f, m_playButtonText.getLocalBounds().height / 2.f);
	m_playButtonText.setFillColor(sf::Color::White);
	m_playButtonText.setPosition(m_playButton.getPosition());

	m_playButton.update(true);

	m_backButton.setPosition(m_view.getCenter() + sf::Vector2f{ 150.f, 270.f });

	m_backButtonText.setOrigin(m_backButtonText.getLocalBounds().width / 2.f, m_backButtonText.getLocalBounds().height / 2.f);
	m_backButtonText.setFillColor(sf::Color::Black);
	m_backButtonText.setPosition(m_backButton.getPosition());
}

void CharacterSelectionState::update()
{
	delayTime = delayClock.getElapsedTime().asSeconds();

	// Move right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right) && delayTime > 0.18f)
	{
		if (m_onHoverButton < m_smallCharacterPortraits.size() - 1)
		{
			++m_onHoverButton;

			delayClock.restart();
		}
	}
	// Move left
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left) && delayTime > 0.18f)
	{
		if (m_onHoverButton > 0)
		{
			--m_onHoverButton;

			delayClock.restart();
		}
	}

	// Upate the visual design of the buttons (according to its state -> onHover OR not onHover)
	for (size_t i = 0; i < m_smallCharacterPortraits.size(); ++i)
	{
		if (m_playerChoice == 1)
		{
			m_smallCharacterPortraits[i].update(i == m_onHoverButton, sf::Color::Magenta);
		}
		else if (m_playerChoice == 2)
		{
			m_smallCharacterPortraits[i].update(i == m_onHoverButton, sf::Color::Yellow);
		}
		else
		{
			m_smallCharacterPortraits[i].update(i == m_onHoverButton, sf::Color::White);
		}
	}

	// Button pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter) && delayTime > 0.18f)
	{
		selectCharacter();
		delayClock.restart();
	}
}

void CharacterSelectionState::render()
{
	for (auto& characterPortrait : m_bigCharacterPortraits)
	{
		m_window.draw(characterPortrait.getSprite());
	}

	for (auto& characterPortrait : m_smallCharacterPortraits)
	{
		m_window.draw(characterPortrait.m_portraitBorder);
		m_window.draw(characterPortrait.getSprite());
	}

	for (auto& playerPortraitText : m_playerPortraitsText)
	{
		m_window.draw(playerPortraitText);
	}

	for (auto& portraitBorder : m_portraitsBorder)
	{
		m_window.draw(portraitBorder);
	}
	
	if (m_playerChoice == 1 || m_playerChoice == 2)
	{
		m_window.draw(m_playerTurn);
	}

	if (m_playerChoice > 2)
	{
		m_window.draw(m_playButton.getSprite());
		m_window.draw(m_playButtonText);

		m_window.draw(m_backButton.getSprite());
		m_window.draw(m_backButtonText);
	}
}

void CharacterSelectionState::selectCharacter()
{
	if (m_onHoverButton == 0)
	{
		if (m_playerChoice == 1)
		{
			m_bigCharacterPortraits.emplace_back(CharacterPortraitUI{ "fireKnightPortrait", "./assets/portrait_fire_knight.png", m_view.getCenter() - sf::Vector2f{250.f, 0.f}, 5.f });
			m_playerTurn.setString("Player 2:");
			m_playerTurn.setFillColor(sf::Color::Yellow);
		}
		else if (m_playerChoice == 2)
		{
			m_bigCharacterPortraits.emplace_back(CharacterPortraitUI{ "fireKnightPortrait", "./assets/portrait_fire_knight.png", m_view.getCenter() + sf::Vector2f{250.f, 0.f}, 5.f });
		}
	}
	else if (m_onHoverButton == 1)
	{
		if (m_playerChoice == 1)
		{
			m_bigCharacterPortraits.emplace_back(CharacterPortraitUI{ "windHashashinPortrait", "./assets/portrait_wind_hashashin.png", m_view.getCenter() - sf::Vector2f{250.f, 0.f}, 5.f });
			m_playerTurn.setString("Player 2:");
			m_playerTurn.setFillColor(sf::Color::Yellow);
		}
		else if (m_playerChoice == 2)
		{
			m_bigCharacterPortraits.emplace_back(CharacterPortraitUI{ "windHashashinPortrait", "./assets/portrait_wind_hashashin.png", m_view.getCenter() + sf::Vector2f{250.f, 0.f}, 5.f });
		}
	}
	++m_playerChoice;
}
