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
		m_smallCharacterPortraits[i].update(i == m_onHoverButton);
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
		m_window.draw(characterPortrait.m_portraitBorder);
		m_window.draw(characterPortrait.getSprite());
	}

	for (auto& characterPortrait : m_smallCharacterPortraits)
	{
		m_window.draw(characterPortrait.m_portraitBorder);
		m_window.draw(characterPortrait.getSprite());
	}
}

void CharacterSelectionState::selectCharacter()
{
	if (m_onHoverButton == 0)
	{
		if (m_playerChoice == 1)
		{
			m_bigCharacterPortraits.emplace_back(CharacterPortraitUI{ "fireKnightPortrait", "./assets/portrait_fire_knight.png", m_view.getCenter() - sf::Vector2f{250.f, 0.f}, 5.f });
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
		}
		else if (m_playerChoice == 2)
		{
			m_bigCharacterPortraits.emplace_back(CharacterPortraitUI{ "windHashashinPortrait", "./assets/portrait_wind_hashashin.png", m_view.getCenter() + sf::Vector2f{250.f, 0.f}, 5.f });
		}
	}
	++m_playerChoice;
}
