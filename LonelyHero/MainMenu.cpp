#include "MainMenu.h"
#include <iostream>
MainMenu::MainMenu()
{
	if (!m_font.loadFromFile("./fonts/Minecraft.ttf"))
	{
		std::cout << "Error loading font\n";
	}

	sf::RectangleShape temp1{ sf::Vector2f{50.f, 50.f} };

	temp1.setPosition(30.f, 30.f);

	temp1.setOutlineColor(sf::Color::Red);
	temp1.setOutlineThickness(1.f);

	sf::Text temp2{ "Player", m_font };
	temp2.setCharacterSize(24);
	temp2.setFillColor(sf::Color::Blue);

	temp2.setPosition(temp1.getPosition());

	buttonsRectangle.emplace_back(temp1);
	buttonsText.emplace_back(temp2);
}
