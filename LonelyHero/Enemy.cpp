#include "Enemy.h"

Enemy::Enemy(sf::Vector2f firstPosition, const sf::Vector2f& playerPosition)
	: SwordEntity{ firstPosition }
	, m_playerPosition{ playerPosition }
{
	m_hitboxWidth = constants::windHashashinSwordHitboxWidthAttack1;
	m_hitboxHeight = constants::windHashashinSwordHitboxHeight;
	m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);

	m_attackHitbox.setFillColor(sf::Color{255, 0, 0, 50});
	m_attackHitbox.setOutlineThickness(1.f);

	// Initialize starting/ending attackings' frames
	m_attack1StartingFrame = 0;
	m_attack1EndingFrame = 4;
	m_attack2StartingFrame = 1;
	m_attack2EndingFrame = 7;

	m_entityName = "enemy";
	initTexturesMap();

	// Initialize sprite
	m_spriteWidth = constants::windHashashinSpriteWidth;
	m_spriteHeight = constants::windHashashinSpriteHeight;
	m_spriteScale = constants::windHashashinSpriteScale;
	m_sprite.setTexture(*m_texturesManager->loadAndGetTexture(m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle"))));
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ constants::windHashashinShapeWidth, constants::windHashashinShapeHeight});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	m_jumpHeight = constants::enemyJumpHeight;
	m_hp = constants::enemyHp;

	// Generates a random seed
	std::random_device rd;
	// Mersenne Twister random number generator
	std::mt19937 gen(rd());
	// Generates uniform distributed random number in a specific interval
	std::uniform_real_distribution<> distribution1(constants::minEnemySpeed, constants::maxEnemySpeed);
	std::uniform_real_distribution<> distribution2(constants::minEnemyDistanceFromPlayer, constants::maxEnemyDistanceFromPlayer);

	m_speed = static_cast<float>(distribution1(gen));
	m_distanceFromPlayer = static_cast<float>(distribution2(gen));
}

void Enemy::update(float& deltaTime)
{
	updateDeath();

	// Only called if hp > 0
	if (!m_dying)
	{
		bool conditionRunLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A);
		bool conditionRunRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D);
		bool conditionJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W);

		/*bool conditionRunLeft = m_playerPosition.x < getPosition().x - m_distanceFromPlayer;
		bool conditionRunRight = m_playerPosition.x > getPosition().x + m_distanceFromPlayer;
		bool conditionJump = (((m_playerPosition.y - constants::fireKnightShapeHeight / 2.f) < (getPosition().y - getSize().y / 2.f)) && m_isCollidingHorizontally);*/

		updateMovement(conditionRunLeft, conditionRunRight, conditionJump, deltaTime);

		/*m_timeBetweenAttacks = m_timeBetweenAttacksClock.getElapsedTime().asSeconds();
		bool conditionAttack = (m_velocity.x == 0.f && m_timeBetweenAttacks > constants::timeBetweenEnemyAttacks);*/

		bool conditionAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::V);

		if (m_currentTexture == "enemyAttacking1")
		{
			m_hitboxWidth = constants::windHashashinSwordHitboxWidthAttack1;
			m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);
		}
		else if (m_currentTexture == "enemyAttacking2")
		{
			m_hitboxWidth = constants::windHashashinSwordHitboxWidthAttack2;
			m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);
		}

		updateAttack(conditionAttack);

		if (m_currentTexture == "enemyAttacking1")
		{
			m_damage = 100;
		}
		else if (m_currentTexture == "enemyAttacking2")
		{
			m_damage = 50;
		}

		/*if (m_isAttacking)
		{
			m_timeBetweenAttacksClock.restart();
			m_timeBetweenAttacks = 0.f;
		}*/

		updateDamage();

		move(deltaTime);
	}

	if (!m_dead)
	{
		updateGravityWhenDying(deltaTime);
		updateLimits();
	}
}
