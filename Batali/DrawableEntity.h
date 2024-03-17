#pragma once

#include "TextureManager.h"
#include "Constants.h"

using namespace constants;

class DrawableEntity
{
public:
	DrawableEntity();
	virtual ~DrawableEntity() = default;

	// Sets sprite's texture
	void setTexture(const std::string& textureName, const std::string& texturePath);

	// DrawableEntity flip
	void flipSprite(float scale = 1.f) { m_sprite.setScale(-scale, scale); }

	/* Setters */

	void setSpritePosition(sf::Vector2f position) { m_sprite.setPosition(position); }

	/* Getters */

	const sf::Sprite& getSprite() const { return m_sprite; }
	const sf::Vector2f getSpriteSize() const { return sf::Vector2f{static_cast<float>(m_spriteWidth), static_cast<float>(m_spriteHeight)}; }
	const sf::Vector2f getSpritePosition() const { return m_sprite.getPosition(); }

protected:
	// Singleton Pattern
	TextureManager& m_texturesManager;

	sf::Sprite m_sprite{};

	int m_spriteWidth{};
	int m_spriteHeight{};
};
