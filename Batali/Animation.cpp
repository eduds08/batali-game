#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
	if (m_texture)
	{
		delete m_texture;
		m_texture = nullptr;
	}
}

void Animation::setTexture(const std::string& name, const std::string& path)
{
	// Checks if the texture isn't already set, so it doesn't set the same sprite more than once
	if (m_name != name)
	{
		//m_isPlayedOnce = loopAnimation;
		m_animationEnd = false;
		m_currentTextureFrameIndex = 0;
		m_texture = m_texturesManager.loadAndGetTexture(name, path).get();
		//setTexture(textureName, texturePath);
		m_totalAmountFrames = m_texture->getSize().x / getSize().x;
		m_name = name;
		//m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth * m_frameCount, 0, m_spriteWidth, m_spriteHeight });
	}
}

void Animation::update()
{
	if (!m_animationEnd)
	{
		m_currentTextureFrame = sf::IntRect{ static_cast<int>(m_frameSize.x )* m_currentTextureFrameIndex, 0, static_cast<int>(m_frameSize.x), static_cast<int>(m_frameSize.y )};
		++m_currentTextureFrameIndex;
	}

	if (m_currentTextureFrameIndex == m_totalAmountFrames)
	{
		m_currentTextureFrameIndex = 0;
		if (m_isPlayedOnce)
		{
			m_animationEnd = true;
		}
	}
}
