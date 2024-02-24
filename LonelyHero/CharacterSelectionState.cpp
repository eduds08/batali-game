#include "CharacterSelectionState.h"

CharacterSelectionState::CharacterSelectionState(sf::RenderWindow& window, const std::string& chosenGamemode)
	: StateContext{ window }
	, m_chosenGamemode{ chosenGamemode }
{
	m_currentState = constants::characterSelectionState;

	m_view = m_window.getDefaultView();
	m_view.setCenter(0.f, 0.f);
	m_window.setView(m_view);

	m_playerPortraitsText[1].setString(m_chosenGamemode == "singleplayer" ? "Enemy:" : "Player 2:");

	m_smallCharacterPortraits.emplace_back(CharacterPortraitUI{ "fireKnightPortrait", "./assets/portrait_fire_knight.png", m_view.getCenter() - sf::Vector2f{50.f, -400.f}, false });
	m_smallCharacterPortraits.emplace_back(CharacterPortraitUI{ "windHashashinPortrait", "./assets/portrait_wind_hashashin.png", m_view.getCenter() + sf::Vector2f{50.f, 400.f}, false });

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

	initButton("Play", m_view.getCenter() + sf::Vector2f{ -150.f, 270.f });
	initButton("Back", m_view.getCenter() + sf::Vector2f{ 150.f, 270.f });
}

void CharacterSelectionState::update()
{
	if (m_playerChoice == 1 || m_playerChoice == 2)
	{
		delayTime = delayClock.getElapsedTime().asSeconds();
		updateCharacterSelectionButtons(delayTime);
	}
	else
	{
		delayTime = delayClock.getElapsedTime().asSeconds();
		updateButtonsAfterSelection(delayTime);
	}

	delayTime = delayClock.getElapsedTime().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Y) && delayTime > 0.7f)
	{
		m_playerTurn.move(sf::Vector2f{ 5.f, 0.f });
		std::cout << m_playerTurn.getPosition().x << '\n';
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
		for (auto& button : m_buttons)
		{
			m_window.draw(button.getSprite());
		}
		
		for (auto& buttonText : m_buttonsTexts)
		{
			m_window.draw(buttonText);
		}
	}
}

void CharacterSelectionState::updateCharacterSelectionButtons(float& delayTime)
{
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

	// Upate the visual design of the buttons (according to its state -> onHover OR not onHover)
	for (size_t i = 0; i < m_smallCharacterPortraits.size(); ++i)
	{
		if (m_playerChoice == 1)
		{
			m_smallCharacterPortraits[i].update(i == m_onHoverCharacterButton, sf::Color::Magenta);
		}
		else if (m_playerChoice == 2)
		{
			m_smallCharacterPortraits[i].update(i == m_onHoverCharacterButton, sf::Color::Yellow);
		}
	}

	// Button pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter) && delayTime > 0.18f)
	{
		selectCharacter();
		delayClock.restart();
	}
}

void CharacterSelectionState::updateButtonsAfterSelection(float& delayTime)
{
	// Move right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right) && delayTime > 0.18f)
	{
		if (m_onHoverButton < m_buttons.size() - 1)
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
	for (size_t i = 0; i < m_buttons.size(); ++i)
	{
		m_buttons[i].update(i == m_onHoverButton);
		m_buttonsTexts[i].setPosition(m_buttons[i].getPosition());
		m_buttonsTexts[i].setFillColor(sf::Color::Black);

		if (i == m_onHoverButton)
		{
			m_buttonsTexts[i].setPosition(m_buttons[i].getPosition() + sf::Vector2f{ 0.f, 2.f });
			m_buttonsTexts[i].setFillColor(sf::Color::White);
		}
	}

	// Button pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter) && delayTime > 0.18f)
	{
		pressButton();
	}
}

void CharacterSelectionState::initButton(const std::string& text, sf::Vector2f position)
{
	m_buttons.emplace_back(ButtonUI{ "button", "./assets/ui/button.png", position });

	sf::Text buttonText{ text, m_font };
	buttonText.setOrigin(buttonText.getLocalBounds().width / 2.f, buttonText.getLocalBounds().height / 2.f);
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setPosition(m_buttons.back().getPosition());

	m_buttonsTexts.emplace_back(buttonText);
}

void CharacterSelectionState::pressButton()
{
	if (m_onHoverButton == 0)
	{
		if (m_chosenGamemode == "singleplayer")
		{
			m_currentState = constants::characterSelectionToSingleplayerTransition;
		}
		else if (m_chosenGamemode == "multiplayer")
		{
			m_currentState = constants::characterSelectionToMultiplayerTransition;
		}
	}
	else if (m_onHoverButton == 1)
	{
		// back to character selection
	}
}

void CharacterSelectionState::selectCharacter()
{
	if (m_onHoverCharacterButton == 0)
	{
		if (m_playerChoice == 1)
		{
			m_bigCharacterPortraits.emplace_back(CharacterPortraitUI{ "fireKnightPortrait", "./assets/portrait_fire_knight.png", m_view.getCenter() - sf::Vector2f{250.f, 0.f}, true });
			m_playerTurn.setString(m_chosenGamemode == "singleplayer" ? "Enemy:" : "Player 2:");
			m_playerTurn.setFillColor(sf::Color::Yellow);
			m_playerTurn.setPosition(m_view.getCenter() - sf::Vector2f{ m_chosenGamemode == "singleplayer" ? 140.f : 170.f, -400.f });

			chosenCharacters.emplace_back("fire_knight");
		}
		else if (m_playerChoice == 2)
		{
			m_bigCharacterPortraits.emplace_back(CharacterPortraitUI{ "fireKnightPortrait", "./assets/portrait_fire_knight.png", m_view.getCenter() + sf::Vector2f{250.f, 0.f}, true });
			chosenCharacters.emplace_back("fire_knight");
		}
	}
	else if (m_onHoverCharacterButton == 1)
	{
		if (m_playerChoice == 1)
		{
			m_bigCharacterPortraits.emplace_back(CharacterPortraitUI{ "windHashashinPortrait", "./assets/portrait_wind_hashashin.png", m_view.getCenter() - sf::Vector2f{250.f, 0.f}, true });
			m_playerTurn.setString(m_chosenGamemode == "singleplayer" ? "Enemy:" : "Player 2:");
			m_playerTurn.setFillColor(sf::Color::Yellow);
			m_playerTurn.setPosition(m_view.getCenter() - sf::Vector2f{ m_chosenGamemode == "singleplayer" ? 140.f : 170.f, -400.f });

			chosenCharacters.emplace_back("wind_hashashin");
		}
		else if (m_playerChoice == 2)
		{
			m_bigCharacterPortraits.emplace_back(CharacterPortraitUI{ "windHashashinPortrait", "./assets/portrait_wind_hashashin.png", m_view.getCenter() + sf::Vector2f{250.f, 0.f}, true });
			chosenCharacters.emplace_back("wind_hashashin");
		}
	}
	++m_playerChoice;
}
