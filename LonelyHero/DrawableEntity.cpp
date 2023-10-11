#include "DrawableEntity.h"

DrawableEntity::DrawableEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath)
	: m_texturesManager{ &TextureManager::getInstance() }
	, m_spriteWidth{ spriteWidth }
	, m_spriteHeight{ spriteHeight }
	, m_spriteScale{ spriteScale }
{
	m_sprite.setTexture(*m_texturesManager->loadAndGetTexture(textureName, texturePath));
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });
}
