#pragma once

#include "DrawableEntity.h"

class UI : public DrawableEntity
{
public:
	UI() {}
	UI(sf::Vector2f position, const std::string& textureName, const std::string& texturePath);
	~UI() {}

	void setRectTemp(int x);

	void setPosition(sf::Vector2f position) { m_sprite.setPosition(position); }
private:

};

