#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

class MainMenu
{
public:
	MainMenu();
	~MainMenu() {};

	/*sf::RectangleShape temp1;
	sf::Text temp2;*/

	std::vector<sf::RectangleShape> buttonsRectangle{};
	std::vector<sf::Text> buttonsText{};

	sf::View viewTemp{ sf::Vector2f{320.f, 320.f}, sf::Vector2f{640.f, 640.f} };

	//std::map <sf::RectangleShape, sf::Text> m_buttonsMap{};

protected:

	// Talvez um ENUM aqui para os botões (0, 1, 2...)

	std::string m_stateName{"main"};

	sf::Font m_font{}; // vai ir para a classe base

	
	

	/*sf::Text m_text{};
	sf::IntRect button{};*/

	int m_onHoverButton{};
};
