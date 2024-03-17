#include "Projectile.h"

Projectile::Projectile(const std::string& entityName)
	: MovableEntity{}
{
	m_entityName = entityName;
}

void Projectile::updateTexture()
{
	if (m_collided)
	{
		changeCurrentTexture(m_entityName + "Collision", "./assets/" + m_entityName + "/_Collision.png", false);
	}
	else
	{
		changeCurrentTexture(m_entityName + "Projectile", "./assets/" + m_entityName + "/_Projectile.png", true);
	}
}

void Projectile::update(float& deltaTime)
{
	if (!m_collided)
	{
		setVelocity(sf::Vector2f{ m_speed * m_facingRight, 0.f });
		move(deltaTime);
	}
	else
	{
		m_shape.setSize(sf::Vector2f{ 0.f, 0.f });
		m_shape.setPosition(-100.f, -100.f);

		if (m_currentTexture == m_entityName + "Collision" && m_animationEnd)
		{
			m_vanished = true;
		}
	}
}
