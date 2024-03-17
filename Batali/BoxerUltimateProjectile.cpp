#include "BoxerUltimateProjectile.h"

BoxerUltimateProjectile::BoxerUltimateProjectile(sf::Vector2f firstPosition, int direction)
	: Projectile{"boxer_ultimate_projectile" }
{
	m_spriteWidth = 30;
	m_spriteHeight = 30;

	m_facingRight = direction;

	m_speed = 400.f;

	// Initialize sprite
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });
	flipSprite();
	setSpritePosition(firstPosition);

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ 15, 15 });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	setShapePosition(firstPosition);

	// DEBUG
	m_shape.setFillColor(sf::Color{ 255, 0, 0, 50 });
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	changeCurrentTexture(m_entityName + "Projectile", "./assets/" + m_entityName + "/_Projectile.png", true);
}
