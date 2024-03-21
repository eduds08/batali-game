#include "Character.h"
#include "ColliderEntity.h"



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
	m_state->update(*this, deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space))
	{
		handleCondition("JUMP");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z))
	{
		handleCondition("ROLL");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
	{
		handleCondition("RUN");
	}

	/*this->updateMovement(this->m_conditionRunLeft, this->m_conditionRunRight, this->m_conditionJump, deltaTime, this->m_conditionRoll);

	this->updateAttack(this->m_conditionAttack1, this->m_conditionAttack2, this->m_conditionUltimate);

	this->updateDamage();*/

	if (m_collisionDirection.y > 0.f)
	{
		m_velocity.y = 0.f;
	}

	this->move(deltaTime, -(m_spriteHeight - getShapeSize().y) / 2.f);

	this->updateLimits();
}
