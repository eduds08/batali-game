#include "LoopingAnimation.h"

LoopingAnimation::LoopingAnimation(const std::string& name, const sf::Vector2i& frameSize, std::shared_ptr<sf::Texture> texture)
{
	m_texture = texture;
	m_frameSize = frameSize;
	m_name = name;
	m_currentTextureFrameIndex = 0;
	m_totalAmountFrames = static_cast<int>(m_texture->getSize().x) / m_frameSize.x;
	m_currentTextureFrame = { m_frameSize.x * m_currentTextureFrameIndex, 0, m_frameSize.x, m_frameSize.y };
}

LoopingAnimation::~LoopingAnimation()
{
}

void LoopingAnimation::update()
{
	m_currentTextureFrame = { m_frameSize.x * m_currentTextureFrameIndex, 0, m_frameSize.x, m_frameSize.y };
	++m_currentTextureFrameIndex;

	if (m_currentTextureFrameIndex == m_totalAmountFrames)
	{
		m_currentTextureFrameIndex = 0;
	}
}
