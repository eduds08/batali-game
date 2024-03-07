#pragma once

#include "CharacterPortraitUI.h"

class BigCharacterPortraitUI : public CharacterPortraitUI
{
public:
	BigCharacterPortraitUI(const std::string& textureName = "", const std::string& texturePath = "", sf::Vector2f position = sf::Vector2f{ 0.f, 0.f }, sf::Color borderColor = sf::Color::White);
	virtual ~BigCharacterPortraitUI() = default;

private:

};
