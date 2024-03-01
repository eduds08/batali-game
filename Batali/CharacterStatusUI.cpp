#include "CharacterStatusUI.h"

CharacterStatusUI::CharacterStatusUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool onRight)
	: UI{}
{
	init(textureName, texturePath, position, onRight);
}

void CharacterStatusUI::init(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool onRight)
{
	setTexture(textureName, texturePath);

	// Sprite' size of character's logo
	m_spriteWidth = CHARACTER_LOGO_STATUS_WIDTH;
	m_spriteHeight = CHARACTER_LOGO_STATUS_HEIGHT;

	m_healthBar.init("healthBar", "./assets/ui/leftHealthBar.png", position + sf::Vector2f{ static_cast<float>(m_spriteWidth), 0.f }, sf::Vector2i{ HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT });
	m_staminaBar.init("staminaBar", "./assets/ui/leftStaminaBar.png", position + sf::Vector2f{ static_cast<float>(m_spriteWidth), 18.f }, sf::Vector2i{ STAMINA_BAR_WIDTH, STAMINA_BAR_HEIGHT });
	m_manaBar.init("manaBar", "./assets/ui/leftManaBar.png", position + sf::Vector2f{ static_cast<float>(m_spriteWidth), 36.f }, sf::Vector2i{ MANA_BAR_WIDTH, MANA_BAR_HEIGHT });

	if (!onRight)
	{
		flipSprite();

		m_healthBar.flipSprite();
		m_staminaBar.flipSprite();
		m_manaBar.flipSprite();
	}

	setSpritePosition(position);
}

void CharacterStatusUI::update()
{
	m_healthBar.update();
	m_staminaBar.update();
	m_manaBar.update();
}
