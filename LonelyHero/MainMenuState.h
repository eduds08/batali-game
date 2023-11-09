#pragma once

#include "StateContext.h"
#include "ButtonUI.h"
#include <map>

class MainMenuState : public StateContext
{
public:
	MainMenuState(sf::RenderWindow& window);
	virtual ~MainMenuState() = default;

	// Used once on constructor to create the menu buttons
	void initButton(const std::string& text, int position);

	virtual void update();
	virtual void render();

	// Called when user press enter on a button. It checks which button was pressed and then changes the current state according to it
	void pressButton();

private:
	std::vector<ButtonUI> buttons{};
	std::vector<sf::Text> buttonsTexts{};

	sf::Clock delayClock{};
	float delayTime{};

	size_t m_onHoverButton{ 0 };
};
