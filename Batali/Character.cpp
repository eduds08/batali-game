#include "Character.h"

#include "ProjectileEntity.h"
#include "WindHashashin.h"

#include "DeadState.h"
#include "IdleState.h"
#include "RollingState.h"
#include "HittedState.h"

Character::Character(int playerNumber)
	: ColliderEntity{}
	, m_playerNumber{ playerNumber }
{
	// Second player starts facing left
	if (m_playerNumber == 2)
	{
		m_facingRight = -1;
		flipSprite();
	}
}

Character::~Character()
{
	if (m_state)
	{
		delete m_state;
		m_state = nullptr;
	}
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

	m_state->update(*this, deltaTime);

	if (dynamic_cast<DeadState*>(m_state) == nullptr)
	{
		m_velocity.y += GRAVITY * deltaTime;

		this->move(deltaTime, -(m_spriteHeight - getShapeSize().y) / 2.f);


		this->updateLimits();
	}

	m_knockbackVelocity = KNOCKBACK_SPEED;
}

void Character::setState(CharacterState* state)
{
	if (state != nullptr)
	{
		if ((dynamic_cast<AttackingState*>(m_state)) != nullptr)
		{
			if (m_entityName == "wind_hashashin")
			{
				dynamic_cast<WindHashashin*>(this)->setActivateUltimate(false);
			}
		}

		delete m_state;
		m_state = state;
		m_state->enter(*this);
	}
}

bool Character::takeDamage(float attackDirection, int damage)
{
	// Only executed if not already dead and when not immune (on damageCooldown or onRoll)
	if (dynamic_cast<DeadState*>(m_state) == nullptr && dynamic_cast<HittedState*>(m_state) == nullptr)
	{
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
				MovableEntity::flipSprite();
			}
		}
		else
		{
			// attack coming from right
			if (m_facingRight == -1)
			{
				m_facingRight = 1;
				MovableEntity::flipSprite();
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
