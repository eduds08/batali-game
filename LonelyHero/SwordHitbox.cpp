#include "SwordHitbox.h"

SwordHitbox::SwordHitbox()
{
	m_shape.setSize(sf::Vector2f(70.f, 30.f));
	m_shape.setOrigin(m_shape.getSize() / 2.f);

	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);
}

SwordHitbox::~SwordHitbox()
{
}
