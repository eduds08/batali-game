#include "Character.h"

Character::Character(sf::Vector2f firstPosition, int playerNumber, bool isBot, std::shared_ptr<Character> player)
	: SwordEntity{ firstPosition }
	, m_playerNumber{ playerNumber }
	, m_isBot{ isBot }
	, m_player{ player }
{
	if (isBot || playerNumber == 2)
	{
		m_facingRight = -1;
		flipSprite();
	}
}

void Character::update(float& deltaTime)
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
			bool conditionRunLeft = m_player->getPosition().x < getPosition().x - m_distanceFromPlayer;
			bool conditionRunRight = m_player->getPosition().x > getPosition().x + m_distanceFromPlayer;
			bool conditionJump = (((m_player->getPosition().y - m_player->getSize().y / 2.f) < (getPosition().y - getSize().y / 2.f)) && m_isCollidingHorizontally);

			updateMovement(conditionRunLeft, conditionRunRight, conditionJump, deltaTime);

			m_timeBetweenAttacks = m_timeBetweenAttacksClock.getElapsedTime().asSeconds();
			conditionAttack = (m_velocity.x == 0.f && m_timeBetweenAttacks > constants::timeBetweenBotAttacks);
		}

		if (m_currentTexture == m_entityName + "Attacking1")
		{
			m_hitboxWidth = m_entityName == "fire_knight" ? constants::fireKnightSwordHitboxWidthAttack1 : constants::windHashashinSwordHitboxWidthAttack1;
			m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);
		}
		else if (m_currentTexture == m_entityName + "Attacking2")
		{
			m_hitboxWidth = m_entityName == "fire_knight" ? constants::fireKnightSwordHitboxWidthAttack2 : constants::windHashashinSwordHitboxWidthAttack2;
			m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);
		}
		else if (m_currentTexture == m_entityName + "AirAttacking")
		{
			m_hitboxWidth = m_entityName == "fire_knight" ? constants::fireKnightSwordHitboxWidthAirAttacking : constants::windHashashinSwordHitboxWidthAirAttacking;
			m_entityName == "fire_knight" ? m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight * 3 } / 2.f) : m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);
		}

		updateAttack(conditionAttack);

		if (m_currentTexture == m_entityName + "Attacking1")
		{
			m_damage = m_entityName == "fire_knight" ? 100 : 150;
		}
		else if (m_currentTexture == m_entityName + "Attacking2")
		{
			m_damage = m_entityName == "fire_knight" ? 70 : 90;
		}
		else if (m_currentTexture == m_entityName + "AirAttacking")
		{
			m_damage = m_entityName == "fire_knight" ? 80 : 100;
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

void Character::updateTexture()
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
		if (m_isAirAttacking)
		{
			changeCurrentTexture(m_texturesActionName.at("AirAttacking"), m_texturesNamePath.at(m_texturesActionName.at("AirAttacking")), false);
		}
		else
		{
			m_velocity.y > 0.f ? changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true) : changeCurrentTexture(m_texturesActionName.at("Jumping"), m_texturesNamePath.at(m_texturesActionName.at("Jumping")), true);;
		}
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
		if (!m_isAirAttacking)
		{
			m_previousAttackingAnimation == m_entityName + "Attacking1" ? changeCurrentTexture(m_texturesActionName.at("Attacking2"), m_texturesNamePath.at(m_texturesActionName.at("Attacking2")), false) : changeCurrentTexture(m_texturesActionName.at("Attacking1"), m_texturesNamePath.at(m_texturesActionName.at("Attacking1")), false);
		}
	}
}
