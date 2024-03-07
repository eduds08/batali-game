#include "Character.h"

Character::Character(int playerNumber, bool isBot, std::shared_ptr<Character> player)
	: SwordEntity{}
	, m_playerNumber{ playerNumber }
	, m_player{ player }
{
	m_isBot = isBot;

	// Second player or bot starts facing left
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
		if (m_isBot)
		{
			m_conditionRunLeft = m_player->getShapePosition().x < getShapePosition().x - m_distanceFromPlayer;
			m_conditionRunRight = m_player->getShapePosition().x > getShapePosition().x + m_distanceFromPlayer;
			m_conditionJump = (((m_player->getShapePosition().y - m_player->getShapeSize().y / 2.f) < (getShapePosition().y - getShapeSize().y / 2.f)) && m_isCollidingHorizontally);

			m_timeBetweenAttacks = m_timeBetweenAttacksClock.getElapsedTime().asSeconds();
			m_conditionAttack1 = (m_velocity.x == 0.f && m_timeBetweenAttacks > TIME_BETWEEN_ENEMY_ATTACKS);

			m_conditionRoll = false;
		}

		updateMovement(m_conditionRunLeft, m_conditionRunRight, m_conditionJump, deltaTime, m_conditionRoll);

		updateAttack(m_conditionAttack1, m_conditionAttack2, m_conditionUltimate);

		updateDamage();

		move(deltaTime);
	}

	// Entity is dying (still playing dying animation)
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
		m_onWindHashashinUltimate ? changeCurrentTexture(m_texturesActionName.at("_HitOnWindHashashinUltimate"), m_texturesNamePath.at(m_texturesActionName.at("_HitOnWindHashashinUltimate")), false) : changeCurrentTexture(m_texturesActionName.at("Hitted"), m_texturesNamePath.at(m_texturesActionName.at("Hitted")), false);
	}
	else if (m_velocity.y != 0.f && !m_canJump)
	{
		if (m_attackMode == "onAirAttack")
		{
			changeCurrentTexture(m_texturesActionName.at("AirAttack"), m_texturesNamePath.at(m_texturesActionName.at("AirAttack")), false);
		}
		else
		{
			m_velocity.y > 0.f ? changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true) : changeCurrentTexture(m_texturesActionName.at("Jumping"), m_texturesNamePath.at(m_texturesActionName.at("Jumping")), true);;
		}
	}
	else if (m_attackMode == "off")
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
	else if (m_attackMode != "off")
	{
		if (m_attackMode == "onUltimate")
		{
			changeCurrentTexture(m_texturesActionName.at("Ultimate"), m_texturesNamePath.at(m_texturesActionName.at("Ultimate")), false);
		}
		else if (m_attackMode != "onAirAttack")
		{
			if (m_isBot)
			{
				m_previousAttackingAnimation == m_entityName + "Attack1" ? changeCurrentTexture(m_texturesActionName.at("Attack2"), m_texturesNamePath.at(m_texturesActionName.at("Attack2")), false) : changeCurrentTexture(m_texturesActionName.at("Attack1"), m_texturesNamePath.at(m_texturesActionName.at("Attack1")), false);
			}
			else
			{
				if (m_attackMode == "onAttack1")
				{
					changeCurrentTexture(m_texturesActionName.at("Attack1"), m_texturesNamePath.at(m_texturesActionName.at("Attack1")), false);
				}
				else if (m_attackMode == "onAttack2")
				{
					changeCurrentTexture(m_texturesActionName.at("Attack2"), m_texturesNamePath.at(m_texturesActionName.at("Attack2")), false);
				}
			}
		}
	}
}
