#include "Projectile.h"

Projectile::Projectile(sf::Vector2f firstPosition, float direction)
	: AnimatedEntity{}
{
	m_spriteWidth = 25;
	m_spriteHeight = 20;
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	m_sprite.setScale(direction, 1.f);

	changeCurrentTexture("boxerUltimateProjectile", "./assets/boxer/_Projectile.png", true);

	setSpritePosition(firstPosition);
}

void Projectile::updateTexture()
{
	if (m_collided)
	{
		// change texture to explode (loop = false)
	}
	else
	{
		changeCurrentTexture("boxerUltimateProjectile", "./assets/boxer/_Projectile.png", true);
	}
}

void Projectile::update(float& deltaTime)
{
	m_sprite.move(sf::Vector2f{300.f * m_sprite.getScale().x * deltaTime, 0.f});
}
