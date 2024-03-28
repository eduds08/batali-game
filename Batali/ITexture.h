#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class ITexture
{
public:
	virtual ~ITexture() = default;

	virtual void setTexture(const std::string& name, const std::string& path) = 0;

	virtual const std::string& getName() const = 0;

	virtual const sf::Vector2u& getSize() const = 0;
};
