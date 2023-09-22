#pragma once

#include "TextureManager.h"

class DrawableEntity
{
public:
	DrawableEntity(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight);
	virtual ~DrawableEntity() = default;

	virtual void setSpriteTexture(const std::string& textureName, const std::string& texturePath);

	void setShapeSettings(float positionX, float positionY);
	void setSpriteSettings();

	sf::RectangleShape& getShape() { return m_shape; }
	const sf::Sprite& getSprite() const { return m_sprite; }

	//virtual const sf::Vector2f& getPosition() const { return m_shape.getPosition(); }
	//virtual const sf::Vector2f& getSize() const { return m_shape.getSize(); }

protected:
	sf::RectangleShape m_shape{};
	sf::Sprite m_sprite{};

	TextureManager m_texturesManager{};
	
	int m_spriteWidth{};
	int m_spriteHeight{};

	float m_shapeWidth{};
	float m_shapeHeight{};
};
