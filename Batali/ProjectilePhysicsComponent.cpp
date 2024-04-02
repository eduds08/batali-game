#include "ProjectilePhysicsComponent.h"

#include "GameObject.h"

void ProjectilePhysicsComponent::update(GameObject& gameObject, float& deltaTime)
{
	gameObject.setVelocity(300.f * gameObject.getFacingRight(), gameObject.getVelocity().y);

	move(gameObject, deltaTime);

	/*if (!m_collided)
	{*/
		//setVelocity(sf::Vector2f{ m_speed * m_facingRight, 0.f });
		//move(deltaTime);
	/*}
	else
	{
		m_shape.setSize(sf::Vector2f{ 0.f, 0.f });
		m_shape.setPosition(-100.f, -100.f);

		if (m_currentTexture == m_actorName + "Collision" && m_animationEnd)
		{
			m_vanished = true;
		}
	}*/
}

void ProjectilePhysicsComponent::move(GameObject& gameObject, float& deltaTime)
{
	gameObject.getShape().move(gameObject.getVelocity() * deltaTime);
	gameObject.getSprite().setPosition(gameObject.getShape().getPosition());
}
