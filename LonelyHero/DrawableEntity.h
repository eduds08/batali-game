#pragma once

#include "TextureManager.h"

class DrawableEntity
{
public:
	DrawableEntity(int spriteWidth, int spriteHeight);
	virtual ~DrawableEntity() = default;

	virtual void setSpriteTexture(const std::string& textureName, const std::string& texturePath);

	void setSpriteSettings(sf::Vector2f position);
	
	const sf::Sprite& getSprite() const { return m_sprite; }

protected:
	sf::Sprite m_sprite{};

	TextureManager m_texturesManager{};
	
	int m_spriteWidth{};
	int m_spriteHeight{};
};
