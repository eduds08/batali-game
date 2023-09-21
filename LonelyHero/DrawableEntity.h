#pragma once

#include "TextureManager.h"
#include "AnimationManager.h"

class DrawableEntity
{
public:
	DrawableEntity(int frameWidth, int frameHeight);
	~DrawableEntity() {}

	virtual void setSpriteTexture(const std::string& textureName, const std::string& texturePath);
	void setSpriteSettings(float xCoord, float yCoord, float scaleX = 1.f, float scaleY = 1.f);

	const sf::Sprite& getSprite() const { return m_sprite; }
	const sf::FloatRect& getBounds() const { return m_sprite.getGlobalBounds(); }

protected:
	sf::Sprite m_sprite{};
	TextureManager m_texturesManager{};
	
	int m_frameWidth{};
	int m_frameHeight{};
};
