#pragma once

#include "DrawableEntity.h"
#include "Constants.h"

class UI : public DrawableEntity
{
public:
	UI(sf::Vector2f position, const std::string& textureName, const std::string& texturePath);
	virtual ~UI() = default;

	void setPosition(sf::Vector2f position) { m_sprite.setPosition(position); }
	sf::Vector2f getPosition() { return m_sprite.getPosition(); }
protected:

};
