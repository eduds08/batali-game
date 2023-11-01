#pragma once

#include "MenuContext.h"

class MainMenuState : public MenuContext
{
public:
	MainMenuState(sf::RenderWindow& window);
	virtual ~MainMenuState() = default;

	void initButton(const std::string& text, int position);

	virtual void update();
	virtual void render();

	void pressButton();

private:

	std::vector<sf::RectangleShape> buttonsShapes{};
	std::vector<sf::Text> buttonsTexts{};

	sf::Clock delayClock{};
	float delayTime{};

	// Talvez um ENUM aqui para os botões (0, 1, 2...)

	int m_onHoverButton{ 0 };
};
