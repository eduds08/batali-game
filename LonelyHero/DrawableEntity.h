#pragma once

#include "TextureManager.h"

class DrawableEntity
{
public:
	DrawableEntity(int spriteWidth, int spriteHeight, float spriteScale = 1.f);
	virtual ~DrawableEntity() = default;

	virtual void setSpriteTexture(const std::string& textureName, const std::string& texturePath);
	
	const sf::Sprite& getSprite() const { return m_sprite; }

protected:
	sf::Sprite m_sprite{};

	TextureManager* m_texturesManager;
	
	int m_spriteWidth{};
	int m_spriteHeight{};

	float m_spriteScale{ 1.f };
};
