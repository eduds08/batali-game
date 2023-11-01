#include "MenuContext.h"

MenuContext::MenuContext(sf::RenderWindow& window)
	: m_window{ window }
{
	m_font.loadFromFile("./fonts/Minecraft.ttf");
}
