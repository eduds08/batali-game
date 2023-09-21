#include "DrawableEntity.h"
#include "Game.h"

DrawableEntity::DrawableEntity(int frameWidth, int frameHeight, int frameAmount) 
	: m_frameWidth{ frameWidth }
	, m_frameHeight{ frameHeight }
	, m_frameAmount{ frameAmount }
{
}

DrawableEntity::~DrawableEntity()
{
}

void DrawableEntity::setSpriteTexture(const std::string& textureName, const std::string& texturePath)
{
	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(textureName, texturePath));
	m_currentSprite = textureName;
}

void DrawableEntity::setSpriteSettings(float xCoord, float yCoord, float scaleX, float scaleY)
{
	m_sprite.setPosition(xCoord, yCoord);

	m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);

	m_sprite.setScale(scaleX, scaleY);
}

void DrawableEntity::updateAnimation(float& deltaTime)
{
	float switchTime = 0.1f;
	m_totalTime += deltaTime;

	if (m_totalTime >= switchTime)
	{
		m_totalTime -= switchTime;
		AnimationManager::animateSprite(m_sprite, m_frameAmount, m_frameWidth, m_frameHeight, m_textureFrameCount);
	}

	//AnimationManager::animateSprite(m_sprite, m_frameAmount, m_frameWidth, m_frameHeight, m_textureFrameCount);
}
