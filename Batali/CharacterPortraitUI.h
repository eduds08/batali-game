#pragma once

#include "UI.h"

class CharacterPortraitUI : public UI
{
public:
	CharacterPortraitUI(const std::string& textureName = "", const std::string& texturePath = "", sf::Vector2f position = sf::Vector2f{0.f, 0.f}, bool isBig = false, sf::Color borderColor = sf::Color::White);
	virtual ~CharacterPortraitUI() = default;

	void init(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool isBig = false, sf::Color borderColor = sf::Color::White);

	// Outline border
	sf::RectangleShape m_portraitBorder{};

	void update(bool onHover, sf::Color color);
};
