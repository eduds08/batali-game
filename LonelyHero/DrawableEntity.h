#pragma once

#include "TextureManager.h"

class DrawableEntity
{
public:
	DrawableEntity(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight);
	virtual ~DrawableEntity() = default;

	virtual void setSpriteTexture(const std::string& textureName, const std::string& texturePath);

	void setShapeSettings(sf::Vector2f position);
	void setSpriteSettings();

	sf::RectangleShape& getShape() { return m_shape; }
	const sf::Sprite& getSprite() const { return m_sprite; }

protected:
	sf::RectangleShape m_shape{};
	sf::Sprite m_sprite{};

	TextureManager m_texturesManager{};
	
	int m_spriteWidth{};
	int m_spriteHeight{};

	float m_shapeWidth{};
	float m_shapeHeight{};
};
