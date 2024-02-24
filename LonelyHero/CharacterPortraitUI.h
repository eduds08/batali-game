#pragma once

#include "UI.h"

class CharacterPortraitUI : public UI
{
public:
	CharacterPortraitUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool isBig);
	virtual ~CharacterPortraitUI() = default;

	sf::RectangleShape m_portraitBorder{};

	void update(bool onHover, sf::Color color);
private:
	bool m_isBig{};
};
