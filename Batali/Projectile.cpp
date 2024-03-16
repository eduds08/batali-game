#include "Projectile.h"

Projectile::Projectile(sf::Vector2f firstPosition, float direction)
	: MovableEntity{}
{
	m_spriteWidth = 30;
	m_spriteHeight = 30;
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	m_sprite.setScale(direction, 1.f);

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ 15, 15 });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);

	// DEBUG
	m_shape.setFillColor(sf::Color{ 255, 0, 0, 50 });
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	changeCurrentTexture("boxerUltimateProjectile", "./assets/boxer/_Projectile.png", true);

	setSpritePosition(firstPosition);
}

void Projectile::updateTexture()
{
	if (m_collided)
	{
		changeCurrentTexture("boxerUltimateProjectileExplosion", "./assets/boxer/_Explosion.png", false);
	}
	else
	{
		changeCurrentTexture("boxerUltimateProjectile", "./assets/boxer/_Projectile.png", true);
	}
}

void Projectile::update(float& deltaTime)
{
	if (!m_collided)
	{
		setVelocity(sf::Vector2f{ 300.f * m_sprite.getScale().x, 0.f });
		move(deltaTime);
	}

	if (m_collided && m_animationEnd)
	{
		m_vanished = true;
	}
}
