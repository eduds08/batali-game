#pragma once

#include "UI.h"

class CharacterPortraitUI : public UI
{
public:
	CharacterPortraitUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool isBig, sf::Color borderColor = sf::Color::White);
	virtual ~CharacterPortraitUI() = default;

	// Outline border
	sf::RectangleShape m_portraitBorder{};

	void update(bool onHover, sf::Color color);

	void setSpriteTexture(const std::string& textureName, const std::string& texturePath);
private:
	// Big or small portrait
	bool m_isBig{};
};
