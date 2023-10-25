#pragma once

#include "TextureManager.h"

class DrawableEntity
{
public:
	DrawableEntity();
	virtual ~DrawableEntity() = default;
	
	sf::Sprite& getSprite() { return m_sprite; }

protected:
	// Singleton Pattern
	TextureManager* m_texturesManager;

	sf::Sprite m_sprite{};

	int m_spriteWidth{};
	int m_spriteHeight{};
};
