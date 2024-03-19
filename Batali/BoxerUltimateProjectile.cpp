#include "BoxerUltimateProjectile.h"

BoxerUltimateProjectile::BoxerUltimateProjectile(sf::Vector2f firstPosition, int direction)
	: Projectile{ "boxer_ultimate" }
{
	m_spriteWidth = BOXER_ULTIMATE_PROJECTILE_SPRITE_WIDTH;
	m_spriteHeight = BOXER_ULTIMATE_PROJECTILE_SPRITE_HEIGHT;

	m_facingRight = direction;

	m_speed = 400.f;

	// Initialize sprite
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });
	flipSprite();
	setSpritePosition(firstPosition);

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ BOXER_ULTIMATE_PROJECTILE_SHAPE_WIDTH, BOXER_ULTIMATE_PROJECTILE_SHAPE_HEIGHT });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	setShapePosition(firstPosition);

	// DEBUG
	m_shape.setFillColor(sf::Color{ 255, 0, 0, 50 });
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	changeCurrentTexture(m_entityName + "Projectile", "./assets/" + m_entityName + "/_Projectile.png", true);
}
