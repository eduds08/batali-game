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

	if (m_state->getStateName() != "DeadState")
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
		if (m_state->getStateName() == "AttackingState")
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
