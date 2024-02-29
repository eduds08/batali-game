#include "CharacterStatusUI.h"

CharacterStatusUI::CharacterStatusUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool onRight)
	: UI{}
	, m_healthBar{}
	, m_staminaBar{}
	, m_manaBar{}
{
	setTexture(textureName, texturePath);

	// Sprite' size of character's logo
	m_spriteWidth = 78;
	m_spriteHeight = 72;

	if (!onRight)
	{
		flipSprite(0.75f);

		m_healthBar.flipSprite(0.75f);
		m_staminaBar.flipSprite(0.75f);
		m_manaBar.flipSprite(0.75f);

		m_healthBar.setPosition(position - sf::Vector2f{ 78.f * 3.f / 4.f, 0.f });
		m_staminaBar.setPosition(position - sf::Vector2f{ 78.f * 3.f / 4.f, -18.f * 3.f / 4.f });
		m_manaBar.setPosition(position - sf::Vector2f{ 78.f * 3.f / 4.f, -36.f * 3.f / 4.f });
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

void CharacterStatusUI::init(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool onRight)
{
	setTexture(textureName, texturePath);

	m_healthBar.init("healthBar", "./assets/ui/leftHealthBar.png", position + sf::Vector2f{ 78.f * 3.f / 4.f, 0.f }, sf::Vector2i{153, 18});
	m_staminaBar.init("staminaBar", "./assets/ui/leftStaminaBar.png", position + sf::Vector2f{ 78.f * 3.f / 4.f, 18.f * 3.f / 4.f }, sf::Vector2i{141, 18});
	m_manaBar.init("manaBar", "./assets/ui/leftManaBar.png", position + sf::Vector2f{ 78.f * 3.f / 4.f, 36.f * 3.f / 4.f }, sf::Vector2i{120, 36});

	// Sprite' size of character's logo
	m_spriteWidth = 78;
	m_spriteHeight = 72;

	if (!onRight)
	{
		flipSprite(0.75f);

		m_healthBar.flipSprite(0.75f);
		m_staminaBar.flipSprite(0.75f);
		m_manaBar.flipSprite(0.75f);

		m_healthBar.setPosition(position - sf::Vector2f{ 78.f * 3.f / 4.f, 0.f });
		m_staminaBar.setPosition(position - sf::Vector2f{ 78.f * 3.f / 4.f, -18.f * 3.f / 4.f });
		m_manaBar.setPosition(position - sf::Vector2f{ 78.f * 3.f / 4.f, -36.f * 3.f / 4.f });
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
