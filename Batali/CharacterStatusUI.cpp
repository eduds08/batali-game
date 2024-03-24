#include "CharacterStatusUI.h"

CharacterStatusUI::CharacterStatusUI(const std::string& textureName, const std::string& texturePath, Character* character, bool onRight)
	: UI{}
{
	init(textureName, texturePath, character, onRight);
}

void CharacterStatusUI::init(const std::string& textureName, const std::string& texturePath, Character* character, bool onRight)
{
	setTexture(textureName, texturePath);

	// Sprite' size of character's logo
	m_spriteWidth = CHARACTER_LOGO_STATUS_WIDTH;
	m_spriteHeight = CHARACTER_LOGO_STATUS_HEIGHT;

	m_healthBar.init("healthBar", "./assets/ui/leftHealthBar.png", sf::Vector2i{ HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT });
	m_staminaBar.init("staminaBar", "./assets/ui/leftStaminaBar.png", sf::Vector2i{ STAMINA_BAR_WIDTH, STAMINA_BAR_HEIGHT });
	m_manaBar.init("manaBar", "./assets/ui/leftManaBar.png", sf::Vector2i{ MANA_BAR_WIDTH, MANA_BAR_HEIGHT });

	if (onRight)
	{
		flipSprite();

		m_healthBar.flipSprite();
		m_staminaBar.flipSprite();
		m_manaBar.flipSprite();
	}

	if (character != nullptr)
	{
		m_healthBar.setEntityStatus(character->getHp());
		m_staminaBar.setEntityStatus(character->getHp());
		m_manaBar.setEntityStatus(character->getRemainingManaToUltimate());
	}
}

void CharacterStatusUI::update()
{
	m_healthBar.update();
	m_staminaBar.update();
	m_manaBar.update();
}

void CharacterStatusUI::updatePosition(sf::Vector2f viewCenter, sf::Vector2f viewSize, bool onRight)
{
	if (onRight)
	{
		m_healthBar.setSpritePosition(viewCenter + sf::Vector2f{ (viewSize.x / 2.f), -viewSize.y / 2.f } - sf::Vector2f{ CHARACTER_LOGO_STATUS_WIDTH, 0.f });
		m_staminaBar.setSpritePosition(viewCenter + sf::Vector2f{ (viewSize.x / 2.f), -viewSize.y / 2.f } - sf::Vector2f{ CHARACTER_LOGO_STATUS_WIDTH, -1.f * HEALTH_BAR_HEIGHT });
		m_manaBar.setSpritePosition(viewCenter + sf::Vector2f{ (viewSize.x / 2.f), -viewSize.y / 2.f } - sf::Vector2f{ CHARACTER_LOGO_STATUS_WIDTH, -1.f * (HEALTH_BAR_HEIGHT + STAMINA_BAR_HEIGHT)});

		setSpritePosition(viewCenter + sf::Vector2f{ (viewSize.x / 2.f), -viewSize.y / 2.f });
	}
	else
	{
		m_healthBar.setSpritePosition(viewCenter + sf::Vector2f{ -(viewSize.x / 2.f), -viewSize.y / 2.f } + sf::Vector2f{ CHARACTER_LOGO_STATUS_WIDTH, 0.f });
		m_staminaBar.setSpritePosition(viewCenter + sf::Vector2f{ -(viewSize.x / 2.f), -viewSize.y / 2.f } + sf::Vector2f{ CHARACTER_LOGO_STATUS_WIDTH, HEALTH_BAR_HEIGHT });
		m_manaBar.setSpritePosition(viewCenter + sf::Vector2f{ -(viewSize.x / 2.f), -viewSize.y / 2.f } + sf::Vector2f{ CHARACTER_LOGO_STATUS_WIDTH, (HEALTH_BAR_HEIGHT + STAMINA_BAR_HEIGHT) });

		setSpritePosition(viewCenter + sf::Vector2f{ -(viewSize.x / 2.f), -viewSize.y / 2.f });
	}
}

void CharacterStatusUI::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	window.draw(m_healthBar.getSprite());
	window.draw(m_staminaBar.getSprite());
	window.draw(m_manaBar.getSprite());
}
