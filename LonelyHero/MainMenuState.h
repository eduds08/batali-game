#pragma once

#include "ButtonAuxState.h"
#include "ButtonUI.h"
#include "BackgroundUI.h"

class MainMenuState : public ButtonAuxState
{
public:
	MainMenuState(sf::RenderWindow& window);
	virtual ~MainMenuState() = default;

	virtual void update();
	virtual void render();

private:

	BackgroundUI m_background{ "menuBackground", "./assets/menuBackground.png", m_window.getDefaultView().getSize() / 2.f, sf::Vector2i{576, 324}, 4.f };

	BackgroundUI m_buttonsBackground{ "menuButtonsBackground", "./assets/menuButtonsBackground.png", sf::Vector2f{m_window.getDefaultView().getSize().x / 2.f, m_window.getDefaultView().getSize().y / 2.f + 1 * 100.f}, sf::Vector2i{308, 462} };

	sf::Text m_gameTitle{"Batali++", m_font};
};
