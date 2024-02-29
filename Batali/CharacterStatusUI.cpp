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

	m_healthBar.init("healthBar", "./assets/ui/leftHealthBar.png", position + sf::Vector2f{ static_cast<float>(m_spriteWidth) * 0.75f, 0.f }, sf::Vector2i{153, 18});
	m_staminaBar.init("staminaBar", "./assets/ui/leftStaminaBar.png", position + sf::Vector2f{ static_cast<float>(m_spriteWidth) * 0.75f, 18.f * 0.75f }, sf::Vector2i{141, 18});
	m_manaBar.init("manaBar", "./assets/ui/leftManaBar.png", position + sf::Vector2f{ static_cast<float>(m_spriteWidth) * 0.75f, 36.f * 0.75f }, sf::Vector2i{120, 36});

	if (!onRight)
	{
		flipSprite(0.75f);

		m_healthBar.flipSprite(0.75f);
		m_staminaBar.flipSprite(0.75f);
		m_manaBar.flipSprite(0.75f);
	}
	else
	{
		setScale(0.75f);

		m_healthBar.setScale(0.75f);
		m_staminaBar.setScale(0.75f);
		m_manaBar.setScale(0.75f);
	}

	setPosition(position);
}

void CharacterStatusUI::update()
{
	m_healthBar.update();
	m_staminaBar.update();
	m_manaBar.update();
}
