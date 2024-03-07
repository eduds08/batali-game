#pragma once

#include "CharacterPortraitUI.h"

class SmallCharacterPortraitUI : public CharacterPortraitUI
{
public:
	SmallCharacterPortraitUI(const std::string& textureName = "", const std::string& texturePath = "", sf::Vector2f position = sf::Vector2f{ 0.f, 0.f });
	virtual ~SmallCharacterPortraitUI() = default;

	void update(bool onHover, sf::Color color);
private:
};
