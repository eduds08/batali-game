#pragma once

#include "ITexture.h"
#include "IAnimation.h"

#include "TexturesManager.h"

class Animation : public ITexture, public IAnimation
{
public:
	Animation();
	virtual ~Animation();

	virtual void setTexture(const std::string& name, const std::string& path);

	virtual void update();

	virtual const std::string& getName() const { return m_name; }

	virtual const sf::Vector2u& getSize() const { return m_frameSize; }

private:
	TexturesManager& m_texturesManager{ TexturesManager::getInstance() };

	sf::Texture* m_texture{};
	sf::IntRect m_currentTextureFrame{};

	std::string m_name{};

	sf::Vector2u m_frameSize{};

	int m_totalAmountFrames{};
	int m_currentTextureFrameIndex{};

	bool m_animationEnd{};
	bool m_isPlayedOnce{};
};
