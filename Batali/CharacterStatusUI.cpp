#include "CharacterStatusUI.h"

CharacterStatusUI::CharacterStatusUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool onRight)
	: UI{textureName, texturePath, position}
	, m_healthBar{ "healthBar", "./assets/ui/leftHealthBar.png", position + sf::Vector2f{ 78.f, 0.f }, sf::Vector2i{153, 18} }
	, m_staminaBar{ "staminaBar", "./assets/ui/leftStaminaBar.png", position + sf::Vector2f{ 78.f, 18.f }, sf::Vector2i{141, 18} }
	, m_manaBar{ "manaBar", "./assets/ui/leftManaBar.png", position + sf::Vector2f{ 78.f, 36.f }, sf::Vector2i{120, 36} }
{
	// Sprite' size of character's logo
	m_spriteWidth = 78;
	m_spriteHeight = 72;

	if (!onRight)
	{
		m_sprite.setScale(-1.f, 1.f);

		m_healthBar.flipSprite();
		m_staminaBar.flipSprite();
		m_manaBar.flipSprite();

		m_healthBar.setPosition(position - sf::Vector2f{ 78.f, 0.f });
		m_staminaBar.setPosition(position - sf::Vector2f{ 78.f, -18.f });
		m_manaBar.setPosition(position - sf::Vector2f{ 78.f, -36.f });
	}
}

void CharacterStatusUI::update()
{
	m_healthBar.update();
	m_staminaBar.update();
	m_manaBar.update();
}
