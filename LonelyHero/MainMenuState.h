#pragma once

#include "StateContext.h"
#include "ButtonUI.h"
#include <map>

class MainMenuState : public StateContext
{
public:
	MainMenuState(sf::RenderWindow& window);
	virtual ~MainMenuState() = default;

	void initButton(const std::string& text, int position);

	virtual void update();
	virtual void render();

	void pressButton();

private:
	std::vector<ButtonUI> buttons{};
	std::vector<sf::Text> buttonsTexts{};

	sf::Clock delayClock{};
	float delayTime{};

	size_t m_onHoverButton{ 0 };
};
