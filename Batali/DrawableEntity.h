#pragma once

#include "TextureManager.h"
#include "Constants.h"

using namespace constants;

class DrawableEntity
{
public:
	DrawableEntity();
	virtual ~DrawableEntity() = default;

	void setPosition(sf::Vector2f position) { m_sprite.setPosition(position); }
	sf::Vector2f getPosition() { return m_sprite.getPosition(); }

	void setScale(float scale) { m_sprite.setScale(scale, scale); }

	void setOrigin(float originX, float originY) { m_sprite.setOrigin(originX, originY); }

	void setTexture(const std::string& textureName, const std::string& texturePath);

	void flipSprite(float scale = 1.f) { m_sprite.setScale(-scale, scale); }

	const sf::Sprite& getSprite() const { return m_sprite; }

	const sf::Vector2f getSpriteSize() const { return sf::Vector2f{static_cast<float>(m_spriteWidth), static_cast<float>(m_spriteHeight)}; }

protected:
	// Singleton Pattern
	TextureManager& m_texturesManager;

	sf::Sprite m_sprite{};

	int m_spriteWidth{};
	int m_spriteHeight{};
};
