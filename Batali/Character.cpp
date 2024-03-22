#include "Character.h"
#include "ColliderEntity.h"

#include "RollingState.h"
#include "IdleState.h"
#include "AttackingState.h"

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


	//updateAttack

	//updateAttackHitbox
	
	//updateDamage


	this->move(deltaTime, -(m_spriteHeight - getShapeSize().y) / 2.f);



	this->updateLimits();
}
