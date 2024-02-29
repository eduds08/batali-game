#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow& window) 
	: ButtonAuxState{ window }
{
	m_currentState = MAIN_MENU_STATE;

	initButton("Singleplayer", sf::Vector2f{ m_window.getDefaultView().getSize().x / 2.f, m_window.getDefaultView().getSize().y / 2.f + 0 * 100.f }, MENU_TO_SINGLEPLAYER);	// 0
	initButton("Multiplayer", sf::Vector2f{ m_window.getDefaultView().getSize().x / 2.f, m_window.getDefaultView().getSize().y / 2.f + 1 * 100.f }, MENU_TO_MULTIPLAYER);	// 1
	initButton("Exit", sf::Vector2f{ m_window.getDefaultView().getSize().x / 2.f, m_window.getDefaultView().getSize().y / 2.f + 2 * 100.f }, EXIT_GAME);							// 2

	m_window.setView(m_window.getDefaultView());

	// Initialize game's title (Batali++)
	m_gameTitle.setCharacterSize(128);
	m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2.f, m_gameTitle.getLocalBounds().height / 2.f);
	m_gameTitle.setPosition(m_window.getDefaultView().getCenter().x, m_window.getDefaultView().getCenter().y - 300.f);
	m_gameTitle.setFillColor(sf::Color{231, 210, 124});
	m_gameTitle.setOutlineThickness(3.f);
	m_gameTitle.setOutlineColor(sf::Color{150, 111, 214});
}

void MainMenuState::update()
{
	updateButtons(true);
}

void MainMenuState::render()
{
	m_window.draw(m_background.getSprite());
	m_window.draw(m_buttonsBackground.getSprite());
	renderButtons();
	m_window.draw(m_gameTitle);
}
