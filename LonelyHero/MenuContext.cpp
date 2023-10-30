#include "MenuContext.h"

MenuContext::MenuContext(sf::RenderWindow& window, float& deltaTime)
	: m_window{window}
	, m_deltaTime{deltaTime}
{
	m_font.loadFromFile("./fonts/Minecraft.ttf");
}
