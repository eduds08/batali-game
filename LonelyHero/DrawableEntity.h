#pragma once

#include "TextureManager.h"

class DrawableEntity
{
public:
	DrawableEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath);
	virtual ~DrawableEntity() = default;
	
	sf::Sprite& getSprite() { return m_sprite; }

protected:
	TextureManager* m_texturesManager;

	sf::Sprite m_sprite{};

	int m_spriteWidth{};
	int m_spriteHeight{};

	float m_spriteScale{};
};
