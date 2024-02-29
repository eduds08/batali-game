#pragma once

#include "UI.h"
#include "StatusBarUI.h"

class CharacterStatusUI : public UI
{
public:
	CharacterStatusUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool onRight = true);
	virtual ~CharacterStatusUI() = default;

	void update();

	StatusBarUI m_healthBar;
	StatusBarUI m_staminaBar;
	StatusBarUI m_manaBar;
private:
	
};
