#include "MovableEntity.h"

MovableEntity::MovableEntity()
	: PhysicalEntity{}
{
}

void MovableEntity::move(float& deltaTime, float offsetPositionY)
{
	m_shape.move(m_velocity * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getShapePosition().x, getShapePosition().y + offsetPositionY});
}
