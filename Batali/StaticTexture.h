#pragma once

#include "ITexture.h"
#include "TexturesManager.h"

class StaticTexture : public ITexture
{
public:
	StaticTexture();
	virtual ~StaticTexture();

	virtual void setTexture(const std::string& name, const std::string& path);

	virtual const std::string& getName() const { return m_name; }

	virtual const sf::Vector2u& getSize() const { return m_texture->getSize(); }

private:
	TexturesManager& m_texturesManager{ TexturesManager::getInstance() };

	sf::Texture* m_texture{};

	std::string m_name{};
};
