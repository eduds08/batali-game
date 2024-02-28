#pragma once

#include "DrawableEntity.h"
#include "Constants.h"

class UI : public DrawableEntity
{
public:
	UI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position);
	virtual ~UI() = default;

	void setPosition(sf::Vector2f position) { m_sprite.setPosition(position); }
	sf::Vector2f getPosition() { return m_sprite.getPosition(); }
protected:

};
