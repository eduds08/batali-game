#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class AbstractAnimation
{
public:
	virtual ~AbstractAnimation() = default;

	virtual void update() = 0;

	virtual void setTexture(sf::Texture* texture) { m_texture = texture; }
	virtual void setName(const std::string& name) { m_name = name; }
	virtual void setFrameSize(sf::Vector2i frameSize) { m_frameSize = frameSize; }

	virtual const std::string& getName() const { return m_name; };
	virtual const sf::Vector2i& getFrameSize() const { return m_frameSize; }
	virtual const sf::Texture& getTexture() const { return *m_texture; }

protected:
	sf::Texture* m_texture{ nullptr };
	sf::IntRect m_currentTextureFrame{};

	std::string m_name{};

	sf::Vector2i m_frameSize{};

	int m_totalAmountFrames{};
	int m_currentTextureFrameIndex{};
};
