#include "PlayedOnceAnimation.h"

PlayedOnceAnimation::PlayedOnceAnimation(const std::string& name, const sf::Vector2i& frameSize, sf::Texture* texture)
{
	m_texture = texture;
	m_frameSize = frameSize;
	m_name = name;
	m_animationEnd = false;
	m_currentTextureFrameIndex = 0;
	m_totalAmountFrames = static_cast<int>(m_texture->getSize().x) / m_frameSize.x;
	m_currentTextureFrame = { m_frameSize.x * m_currentTextureFrameIndex, 0, m_frameSize.x, m_frameSize.y };
}

PlayedOnceAnimation::~PlayedOnceAnimation()
{
	if (m_texture)
	{
		delete m_texture;
		m_texture = nullptr;
	}
}

void PlayedOnceAnimation::update()
{
	// Sets next frame if animationEnd = false
	if (!m_animationEnd)
	{
		m_currentTextureFrame = { m_frameSize.x * m_currentTextureFrameIndex, 0, m_frameSize.x, m_frameSize.y };
		++m_currentTextureFrameIndex;
	}

	// If all frames were played, restarts the animation if loop=true or indicates that animationEnd=true otherwise
	if (m_currentTextureFrameIndex == m_totalAmountFrames)
	{
		m_currentTextureFrameIndex = 0;
		m_animationEnd = true;
		// Talvez emitir um evento "fim da animação"
	}
}
