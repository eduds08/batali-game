#include "AttackHitbox.h"

AttackHitbox::AttackHitbox()
{
	reset();

	m_shape.setFillColor(sf::Color{ 255, 0, 0, 50 });
	m_shape.setOutlineThickness(1.f);
}

void AttackHitbox::reset()
{
	m_shape.setSize(sf::Vector2f{ 0.f, 0.f });
	m_shape.setPosition(-100.f, -100.f);
}
