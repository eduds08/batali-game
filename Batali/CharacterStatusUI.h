#pragma once

#include "UI.h"
#include "StatusBarUI.h"

class CharacterStatusUI : public UI
{
public:
	CharacterStatusUI(const std::string& textureName = "", const std::string& texturePath = "", sf::Vector2f position = sf::Vector2f{0.f, 0.f}, bool onRight = true);
	virtual ~CharacterStatusUI() = default;

	void init(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool onRight = true);

	void update();

	StatusBarUI m_healthBar{};
	StatusBarUI m_staminaBar{};
	StatusBarUI m_manaBar{};
private:
	
};
