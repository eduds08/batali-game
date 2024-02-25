#include "MainMenuState.h"
#include <iostream>
MainMenuState::MainMenuState(sf::RenderWindow& window) 
	: ButtonAuxState{ window }
{
	m_currentState = constants::mainMenuState;

	initButton("Singleplayer", sf::Vector2f{ m_window.getDefaultView().getSize().x / 2.f, m_window.getDefaultView().getSize().y / 2.f + 0 * 100.f }, constants::menuToSingleplayerTransition);	// 0
	initButton("Multiplayer", sf::Vector2f{ m_window.getDefaultView().getSize().x / 2.f, m_window.getDefaultView().getSize().y / 2.f + 1 * 100.f }, constants::menuToMultiplayerTransition);	// 1
	initButton("Exit", sf::Vector2f{ m_window.getDefaultView().getSize().x / 2.f, m_window.getDefaultView().getSize().y / 2.f + 2 * 100.f }, constants::exitingState);							// 2

	m_window.setView(m_window.getDefaultView());
}

void MainMenuState::update()
{
	updateButtons(true);
}

void MainMenuState::render()
{
	renderButtons();
}
