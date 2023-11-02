#include "StateContext.h"

StateContext::StateContext(sf::RenderWindow& window)
	: m_window{ window }
{
	m_font.loadFromFile("./fonts/MinimalPixel_v2.ttf");
}
