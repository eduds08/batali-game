#include "Character.h"

#include "CharacterWithProjectiles.h"
#include "WindHashashin.h"
#include "DeadState.h"
#include "IdleState.h"
#include "RollingState.h"
#include "HittedState.h"

int Character::m_playerNumber{ 1 };

Character::Character()
	: ColliderActor{}
{
	if (m_playerNumber == 1)
	{
		m_inputHandler.bindRunRightCommand(sf::Keyboard::Scancode::D);
		m_inputHandler.bindRunLeftCommand(sf::Keyboard::Scancode::A);
		m_inputHandler.bindJumpCommand(sf::Keyboard::Scancode::W);
		m_inputHandler.bindAttack1Command(sf::Keyboard::Scancode::X);
		m_inputHandler.bindAttack2Command(sf::Keyboard::Scancode::C);
		m_inputHandler.bindRollCommand(sf::Keyboard::Scancode::V);
		m_inputHandler.bindUltimateCommand(sf::Keyboard::Scancode::B);
	}
	else if (m_playerNumber == 2)
	{
		m_facingRight = -1;
		flipSprite();

		m_inputHandler.bindRunRightCommand(sf::Keyboard::Scancode::Right);
		m_inputHandler.bindRunLeftCommand(sf::Keyboard::Scancode::Left);
		m_inputHandler.bindJumpCommand(sf::Keyboard::Scancode::Up);
		m_inputHandler.bindAttack1Command(sf::Keyboard::Scancode::I);
		m_inputHandler.bindAttack2Command(sf::Keyboard::Scancode::O);
		m_inputHandler.bindRollCommand(sf::Keyboard::Scancode::J);
		m_inputHandler.bindUltimateCommand(sf::Keyboard::Scancode::K);
	}

	++m_playerNumber;
}

Character::~Character()
{
	if (m_state)
	{
		delete m_state;
		m_state = nullptr;
	}

	m_playerNumber = 1;
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
	this->updateLimits();
	
	m_knockbackVelocity = KNOCKBACK_SPEED;

	m_inputHandler.handleInput(*this);

	m_state->update(*this, deltaTime);

	if (m_state->getStateName() != "DeadState")
	{
		m_velocity.y += GRAVITY * deltaTime;

		this->move(deltaTime, -(m_spriteHeight - getShapeSize().y) / 2.f);
		
		m_velocity.x = 0.f;
	}
}

void Character::setState(CharacterState* state)
{
	if (state != nullptr)
	{
		if (m_state->getStateName() == "AttackingState")
		{
			if (m_actorName == "wind_hashashin")
			{
				dynamic_cast<WindHashashin*>(this)->setActivateUltimate(false);
			}
		}

		delete m_state;
		m_state = state;
		m_state->enter(*this);
	}
}

void Character::render(sf::RenderWindow& window, bool debugMode)
{
	if (debugMode)
	{
		window.draw(m_shape);
		if (m_state && m_state->getStateName() == "AttackingState")
		{
			window.draw(dynamic_cast<AttackingState*>(m_state)->m_attackHitbox->getShape());
		}
	}

	window.draw(m_sprite);
}
