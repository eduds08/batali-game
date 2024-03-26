#include "Projectile.h"

Projectile::Projectile(const std::string& actorName)
	: MovableActor{}
{
	m_actorName = actorName;
}

void Projectile::updateTexture()
{
	if (m_collided)
	{
		changeCurrentTexture(m_actorName + "Collision", "./assets/" + m_actorName + "/_Collision.png", false);
	}
	else
	{
		changeCurrentTexture(m_actorName + "Projectile", "./assets/" + m_actorName + "/_Projectile.png", true);
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

		if (m_currentTexture == m_actorName + "Collision" && m_animationEnd)
		{
			m_vanished = true;
		}
	}
}
