#include "CharacterPortraitUI.h"

CharacterPortraitUI::CharacterPortraitUI()
	: UI{}
{
}

void CharacterPortraitUI::render(sf::RenderWindow& window)
{
	window.draw(m_portraitBorder);
	window.draw(m_sprite);
}
