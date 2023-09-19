#include "Player.h"

Player::Player()
	: m_sprite{}
	, m_isRunning{ false }
	, m_facingRight{ 1 }
{
	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture("playerIdle", "./_Idle.png"));

	m_sprite.setPosition(300.f, 0.f);
	
	m_sprite.setOrigin(120.f / 2.f, 80.f / 2.f);
	
	m_sprite.setScale(2.f, 2.f);
}

Player::~Player()
{
}

void Player::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
	{
		m_isRunning = true;
		m_facingRight = -1;
		m_sprite.move(-0.1f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
	{
		m_isRunning = true;
		m_facingRight = 1;
		m_sprite.move(0.1f, 0.f);
	}
	else
	{
		m_isRunning = false;
	}
}

void Player::update()
{
	move();

	sf::FloatRect playerBox = m_sprite.getGlobalBounds();

	if (m_isRunning)
	{
		if (m_sprite.getTexture() == m_texturesManager.loadAndGetTexture("playerIdle", "./_Idle.png").get())
		{
			textureFrameCount = 0;
			m_sprite.setTexture(*m_texturesManager.loadAndGetTexture("playerRunning", "./_Run.png"));
		}
	}
	else
	{
		if (m_sprite.getTexture() == m_texturesManager.loadAndGetTexture("playerRunning", "./_Run.png").get())
		{
			textureFrameCount = 0;
			m_sprite.setTexture(*m_texturesManager.loadAndGetTexture("playerIdle", "./_Idle.png"));
		}
	}

	m_sprite.setScale(2.f * m_facingRight, 2.f);

	/*for (it2 = dirtsBound.begin(); it2 != dirtsBound.end(); it2++)
	{
		if (playerBox.intersects(*it2))
		{
		    onFloor = true;
		}
	}*/
}
