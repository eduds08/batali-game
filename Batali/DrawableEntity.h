#pragma once

#include "TextureManager.h"

class DrawableEntity
{
public:
	DrawableEntity();
	virtual ~DrawableEntity() = default;

	const sf::Sprite& getSprite() const { return m_sprite; }

protected:
	// Singleton Pattern
	TextureManager& m_texturesManager;

	sf::Sprite m_sprite{};

	int m_spriteWidth{};
	int m_spriteHeight{};
};
