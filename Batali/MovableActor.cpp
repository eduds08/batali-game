#include "MovableActor.h"

MovableActor::MovableActor()
	: ShapeActor{}
{
}

void MovableActor::move(float& deltaTime, float offsetPositionY)
{
	m_shape.move(m_velocity * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getShapePosition().x, getShapePosition().y + offsetPositionY});
}
