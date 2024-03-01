#pragma once

#include "TextureManager.h"
#include "Constants.h"

using namespace constants;

class DrawableEntity
{
public:
	DrawableEntity();
	virtual ~DrawableEntity() = default;

	void setSpritePosition(sf::Vector2f position) { m_sprite.setPosition(position); }
	const sf::Vector2f getSpritePosition() const { return m_sprite.getPosition(); }

	void setScale(float scale) { m_sprite.setScale(scale, scale); }
	void setOrigin(float originX, float originY) { m_sprite.setOrigin(originX, originY); }
	void flipSprite(float scale = 1.f) { m_sprite.setScale(-scale, scale); }

	void setTexture(const std::string& textureName, const std::string& texturePath);

	const sf::Sprite& getSprite() const { return m_sprite; }
	const sf::Vector2f getSpriteSize() const { return sf::Vector2f{static_cast<float>(m_spriteWidth), static_cast<float>(m_spriteHeight)}; }

protected:
	// Singleton Pattern
	TextureManager& m_texturesManager;

	sf::Sprite m_sprite{};

	int m_spriteWidth{};
	int m_spriteHeight{};
};
