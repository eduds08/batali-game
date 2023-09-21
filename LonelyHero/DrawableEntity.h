#pragma once

#include "TextureManager.h"
#include "AnimationManager.h"

class DrawableEntity
{
public:
	DrawableEntity(int frameWidth, int frameHeight, int frameAmount, float switchAnimationTime);
	~DrawableEntity() {}

	void setSpriteTexture(const std::string& textureName, const std::string& texturePath);
	void setSpriteSettings(float xCoord, float yCoord, float scaleX = 1.f, float scaleY = 1.f);

	const sf::Sprite& getSprite() const { return m_sprite; }
	const sf::FloatRect& getBounds() const { return m_sprite.getGlobalBounds(); }

	void updateAnimation(float& deltaTime);

protected:
	std::string m_currentSprite{};

	sf::Sprite m_sprite{};
	TextureManager m_texturesManager{};

	sf::Time m_elapsed{};
	
	int m_frameWidth{};
	int m_frameHeight{};
	int m_frameAmount{};
	int m_frameCount{ 0 };

	float m_switchAnimationTime{};
	float m_totalAnimationTime{ 0 };
};
