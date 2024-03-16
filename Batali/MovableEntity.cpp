#include "MovableEntity.h"

MovableEntity::MovableEntity()
	: PhysicalEntity{}
{
}

void MovableEntity::move(float& deltaTime)
{

	m_shape.move(m_velocity * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getShapePosition().x, getShapePosition().y - (m_spriteHeight - getShapeSize().y) / 2.f});
}
