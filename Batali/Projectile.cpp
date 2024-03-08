#include "Projectile.h"

Projectile::Projectile(sf::Vector2f firstPosition)
	: AnimatedEntity{}
{
	m_spriteWidth = 25;
	m_spriteHeight = 20;
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

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
