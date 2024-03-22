#include "Character.h"
#include "ColliderEntity.h"

#include "RollingState.h"
#include "IdleState.h"
#include "AttackingState.h"
#include "DeadState.h"
#include "HittedState.h"


Character::Character()
	: ColliderEntity{}
{
}

void Character::handleCondition(const std::string& condition)
{
	CharacterState* state = m_state->handleCondition(*this, condition);

	if (state != nullptr)
	{
		delete m_state;
		m_state = state;

		m_state->enter(*this);
	}
}

void Character::update(float& deltaTime)
{
	m_velocity.x = 0.f;

	if (dynamic_cast<RollingState*>(m_state) == nullptr && dynamic_cast<IdleState*>(m_state) == nullptr)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
		{
			m_facingRight = -1;
			m_velocity.x -= m_speed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
		{
			m_facingRight = 1;
			m_velocity.x += m_speed;
		}

		flipSprite();
	}

	m_state->update(*this, deltaTime);

	m_velocity.y += GRAVITY * deltaTime;


	//updateAttack - Implemented

	//updateAttackHitbox - Implemented
	
	//updateDamage - Half Implemented. Nesse to implement the commented code below:


	//m_knockbackVelocity = KNOCKBACK_SPEED;

	/*if (m_currentTexture != m_entityName + "Hitted" && m_currentTexture != m_entityName + "FastHit")
	{
		m_inDamageCooldown = false;
	}*/


	this->move(deltaTime, -(m_spriteHeight - getShapeSize().y) / 2.f);


	this->updateLimits();
}

bool Character::isCollidingWithAttack(Character& attackingEntity, bool& isUltimateActivate)
{
	if (dynamic_cast<DeadState*>(m_state) == nullptr)
	{
		if (m_shape.getGlobalBounds().intersects(attackingEntity.getAttackHitbox().getGlobalBounds()))
		{
			/*if (attackingEntity.getEntityName() != "wind_hashashin" && attackingEntity.getAttackMode() != "onUltimate")
				m_onFastHit = false;*/
			return true;
		}

		// Was attacked by Wind Hashashin's ultimate activate
		//if (attackingEntity.getEntityName() == "wind_hashashin")
		//{
		//	if (m_shape.getGlobalBounds().intersects(dynamic_cast<WindHashashin*>(&attackingEntity)->getUltimateActivateHitbox().getGlobalBounds()))
		//	{
		//		isUltimateActivate = true;
		//		m_onFreeze = true;
		//		m_onFastHit = true;
		//		dynamic_cast<WindHashashin*>(&attackingEntity)->setActivateUltimate(true);

		//		setShapePosition(attackingEntity.getShapePosition());
		//		setSpritePosition(sf::Vector2f{ getShapePosition().x, getShapePosition().y - (getSpriteSize().y - getShapeSize().y) / 2.f });

		//		setVelocity(sf::Vector2f{ 0.f, 0.f });

		//		return true;
		//	}
		//}

		//// Was attacked by projectiles
		//if (dynamic_cast<ProjectileEntity*>(&attackingEntity) != nullptr)
		//{
		//	for (auto& ultimateProjectile : dynamic_cast<ProjectileEntity*>(&attackingEntity)->getProjectiles())
		//	{
		//		if (m_shape.getGlobalBounds().intersects(ultimateProjectile->getShape().getGlobalBounds()))
		//		{
		//			ultimateProjectile->setCollided(true);
		//			m_onFastHit = true;

		//			return true;
		//		}
		//	}
		//}
	}

	return false;
}

bool Character::takeDamage(float& deltaTime, float attackDirection, int damage)
{
	// Only executed if not already dead and when not immune (on damageCooldown or onRoll)
	if (dynamic_cast<DeadState*>(m_state) == nullptr && dynamic_cast<HittedState*>(m_state) == nullptr)
	{
		//m_inDamageCooldown = true;
		//m_hitted = true;

		m_hp -= damage;

		std::cout << "hit\n---\n";

		/*if (m_remainingManaToUltimate > 0)
		{
			--m_remainingManaToUltimate;
		}*/

		if (attackDirection < 0.f)
		{
			// attack coming from left
			if (m_facingRight == 1)
			{
				m_facingRight = -1;
				flipSprite();
			}
		}
		else
		{
			// attack coming from right
			if (m_facingRight == -1)
			{
				m_facingRight = 1;
				flipSprite();
			}
		}

		handleCondition("HITTED");
		return true;
	}

	return false;
}

void Character::knockbackMove(float& deltaTime, float attackDirection)
{
	if (attackDirection < 0.f)
	{
		// attack coming from left
		m_shape.move(sf::Vector2f{ m_knockbackVelocity, 0.f } *deltaTime);
	}
	else
	{
		// attack coming from right
		m_shape.move(sf::Vector2f{ m_knockbackVelocity * -1.f, 0.f } *deltaTime);
	}

	m_sprite.setPosition(sf::Vector2f{ getShapePosition().x, getShapePosition().y - (m_spriteHeight - getShapeSize().y) / 2.f });
}
