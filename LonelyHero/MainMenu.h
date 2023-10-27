#pragma once

#include "SFML/Graphics.hpp"
#include <map>
#include <string>

class MainMenu
{
public:
	MainMenu();
	virtual ~MainMenu() = default;

protected:

	// Talvez um ENUM aqui para os botões (0, 1, 2...)

	std::string m_stateName{"main"};

	sf::Font m_font{}; // vai ir para a classe base

	std::map <sf::IntRect, sf::Text> m_buttonsMap{};

	/*sf::Text m_text{};
	sf::IntRect button{};*/

	int m_onHoverButton{};
};
