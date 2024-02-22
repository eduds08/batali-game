#include "WindHashashin.h"

WindHashashin::WindHashashin(sf::Vector2f firstPosition, int playerNumber, bool isBot, sf::Vector2f* playerPosition)
	: Character{ firstPosition, playerNumber, isBot, playerPosition }
{
	//m_hitboxWidth = constants::windHashashinSwordHitboxWidthAttack1;
	m_hitboxHeight = constants::windHashashinSwordHitboxHeight;
	//m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);

	m_attackHitbox.setFillColor(sf::Color{255, 0, 0, 50});
	m_attackHitbox.setOutlineThickness(1.f);

	// Initialize starting/ending attackings' frames
	m_attack1StartingFrame = 0;
	m_attack1EndingFrame = 4;
	m_attack2StartingFrame = 1;
	m_attack2EndingFrame = 7;
	m_airAttackingStartingFrame = 3;
	m_airAttackingEndingFrame = 5;

	m_entityName = "enemy";
	initTexturesMap();

	// Initialize sprite
	m_spriteWidth = constants::windHashashinSpriteWidth;
	m_spriteHeight = constants::windHashashinSpriteHeight;
	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle"))));
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

	if (m_isBot)
	{
		// Generates a random seed
		std::random_device rd;
		// Mersenne Twister random number generator
		std::mt19937 gen(rd());
		// Generates uniform distributed random number in a specific interval
		std::uniform_real_distribution<> distribution1(constants::minEnemySpeed, constants::maxEnemySpeed);
		std::uniform_real_distribution<> distribution2(constants::minEnemyDistanceFromPlayer, constants::maxEnemyDistanceFromPlayer);

		m_speed = static_cast<float>(distribution1(gen));
		//m_speed = constants::playerSpeed + 40.f;
		m_distanceFromPlayer = static_cast<float>(distribution2(gen));
	}
	else
	{
		m_speed = constants::playerSpeed;
	}
}

WindHashashin::~WindHashashin()
{
	if (m_playerPosition != nullptr)
	{
		delete m_playerPosition;
		m_playerPosition = nullptr;
	}
}

void WindHashashin::update(float& deltaTime)
{
	updateDeath();

	// Only called if hp > 0
	if (!m_dying)
	{
		bool conditionAttack = false;

		if (!m_isBot)
		{
			if (m_playerNumber == 1)
			{
				bool conditionRunLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left);
				bool conditionRunRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right);
				bool conditionJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up);

				updateMovement(conditionRunLeft, conditionRunRight, conditionJump, deltaTime, sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::NumpadEnter));

				conditionAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Numpad0);
			}
			else if (m_playerNumber == 2)
			{
				bool conditionRunLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A);
				bool conditionRunRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D);
				bool conditionJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W);

				updateMovement(conditionRunLeft, conditionRunRight, conditionJump, deltaTime, sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C));

				conditionAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift);
			}
		}
		else
		{
			bool conditionRunLeft = m_playerPosition->x < getPosition().x - m_distanceFromPlayer;
			bool conditionRunRight = m_playerPosition->x > getPosition().x + m_distanceFromPlayer;
			bool conditionJump = (((m_playerPosition->y - constants::fireKnightShapeHeight / 2.f) < (getPosition().y - getSize().y / 2.f)) && m_isCollidingHorizontally);

			updateMovement(conditionRunLeft, conditionRunRight, conditionJump, deltaTime);

			m_timeBetweenAttacks = m_timeBetweenAttacksClock.getElapsedTime().asSeconds();
			conditionAttack = (m_velocity.x == 0.f && m_timeBetweenAttacks > constants::timeBetweenEnemyAttacks);
		}

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
		else if (m_currentTexture == "enemyAirAttacking")
		{
			m_hitboxWidth = constants::fireKnightSwordHitboxWidthAirAttacking;
			m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight * 3 } / 2.f);
		}

		updateAttack(conditionAttack);

		if (m_currentTexture == "enemyAttacking1")
		{
			m_damage = 150;
		}
		else if (m_currentTexture == "enemyAttacking2")
		{
			m_damage = 90;
		}
		else if (m_currentTexture == "enemyAirAttacking")
		{
			m_damage = 90;
		}

		if (m_isBot)
		{
			if (m_isAttacking)
			{
				m_timeBetweenAttacksClock.restart();
				m_timeBetweenAttacks = 0.f;
			}
		}

		updateDamage();

		move(deltaTime);
	}

	if (!m_dead)
	{
		updateGravityWhenDying(deltaTime);
		updateLimits();
	}
}

void WindHashashin::updateTexture()
{
	if (m_dying)
	{
		changeCurrentTexture(m_texturesActionName.at("Death"), m_texturesNamePath.at(m_texturesActionName.at("Death")), false);
	}
	else if (m_hitted)
	{
		changeCurrentTexture(m_texturesActionName.at("Hitted"), m_texturesNamePath.at(m_texturesActionName.at("Hitted")), false);
	}
	else if (m_velocity.y != 0.f && !m_canJump)
	{
		m_velocity.y > 0.f ? changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true) : changeCurrentTexture(m_texturesActionName.at("Jumping"), m_texturesNamePath.at(m_texturesActionName.at("Jumping")), true);;
	}
	else if (!m_isAttacking)
	{
		if (m_onRoll)
		{
			changeCurrentTexture(m_texturesActionName.at("Roll"), m_texturesNamePath.at(m_texturesActionName.at("Roll")), false);
		}
		else
		{
			m_isRunning ? changeCurrentTexture(m_texturesActionName.at("Running"), m_texturesNamePath.at(m_texturesActionName.at("Running")), true) : changeCurrentTexture(m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle")), true);
		}
	}
	else if (m_isAttacking)
	{
		m_previousAttackingAnimation == m_entityName + "Attacking1" ? changeCurrentTexture(m_texturesActionName.at("Attacking2"), m_texturesNamePath.at(m_texturesActionName.at("Attacking2")), false) : changeCurrentTexture(m_texturesActionName.at("Attacking1"), m_texturesNamePath.at(m_texturesActionName.at("Attacking1")), false);
	}
}

void WindHashashin::updateHitbox()
{
	if ((m_currentTexture == m_entityName + "Attacking1" && m_frameCount > m_attack1StartingFrame && m_frameCount < m_attack1EndingFrame) ||
		(m_currentTexture == m_entityName + "Attacking2" && m_frameCount > m_attack2StartingFrame && m_frameCount < m_attack2EndingFrame) ||
		(m_currentTexture == m_entityName + "AirAttacking" && m_frameCount > m_airAttackingStartingFrame && m_frameCount < m_airAttackingEndingFrame))
	{
		m_attackHitbox.setSize(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight });
		m_attackHitbox.setPosition(getPosition() + sf::Vector2f(m_facingRight * m_attackHitbox.getSize().x / 2.f, 0.f));
	}
	else
	{
		m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	}
}
