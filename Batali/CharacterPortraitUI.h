#pragma once

#include "UI.h"

class CharacterPortraitUI : public UI
{
public:
	CharacterPortraitUI();
	virtual ~CharacterPortraitUI() = default;

	void render(sf::RenderWindow& window);
protected:
	sf::RectangleShape m_portraitBorder{};
};
