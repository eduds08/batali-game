#pragma once

#include "TextureManager.h"

class DrawableEntity
{
public:
	DrawableEntity();
	virtual ~DrawableEntity() = default;

	void setPosition(sf::Vector2f position) { m_sprite.setPosition(position); }
	sf::Vector2f getPosition() { return m_sprite.getPosition(); }

	void setScale(float scale) { m_sprite.setScale(scale, scale); }

	void setOrigin(sf::Vector2f origin) { m_sprite.setOrigin(origin); }

	void setTexture(const std::string& textureName, const std::string& texturePath);

	void flipSprite(float scale = 1.f) { m_sprite.setScale(-scale, scale); }

	const sf::Sprite& getSprite() const { return m_sprite; }

protected:
	// Singleton Pattern
	TextureManager& m_texturesManager;

	sf::Sprite m_sprite{};

	int m_spriteWidth{};
	int m_spriteHeight{};
};
