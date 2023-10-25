#pragma once

#include "DrawableEntity.h"

class UI : public DrawableEntity
{
public:
	UI(sf::Vector2f position, const std::string& textureName, const std::string& texturePath);
	virtual ~UI() = default;

	void setPosition(sf::Vector2f position) { m_sprite.setPosition(position); }
protected:

};
