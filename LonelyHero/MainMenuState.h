#pragma once


#include "MenuContext.h"

class MainMenuState : public MenuContext
{
public:
	MainMenuState(sf::RenderWindow& window, float& deltaTime);
	virtual ~MainMenuState() = default;

	virtual void init();
	//virtual void run();
	virtual void update();
	virtual void render();

	std::vector<sf::RectangleShape> buttonsRectangle{};
	std::vector<sf::Text> buttonsText{};

	sf::View viewTemp{ sf::Vector2f{320.f, 320.f}, sf::Vector2f{640.f, 640.f} };

protected:

	// Talvez um ENUM aqui para os botões (0, 1, 2...)

	std::string m_stateName{"main"};

	sf::Font m_font{}; // vai ir para a classe base

	int m_onHoverButton{};
};
