#pragma once

#include "TextureManager.h"

class DrawableEntity
{
public:
	DrawableEntity(int spriteWidth, int spriteHeight, float spriteScale = 1.f);
	virtual ~DrawableEntity() = default;

	virtual void setSpriteTexture(const std::string& textureName, const std::string& texturePath);
	
	sf::Sprite& getSprite() { return m_sprite; }

protected:
	TextureManager* m_texturesManager;

	sf::Sprite m_sprite{};
	int m_spriteWidth{};
	int m_spriteHeight{};
	float m_spriteScale{};
};
