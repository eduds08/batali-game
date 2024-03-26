#include "AttackingState.h"

#include "IdleState.h"

#include "Character.h"
#include "HittedState.h"
#include "JumpingState.h"
#include "FallingState.h"

#include "ProjectileEntity.h"

#include "WindHashashin.h"

AttackingState::AttackingState(const std::string& attack)
{
	m_stateName = "AttackingState";

	if (attack == "ATTACK_1")
	{
		m_attack = "Attack1";
	}
	if (attack == "ATTACK_2")
	{
		m_attack = "Attack2";
	}
	if (attack == "AIR_ATTACK")
	{
		m_attack = "AirAttack";
	}
	if (attack == "ULTIMATE")
	{
		m_attack = "Ultimate";
	}

	m_attackHitbox = new AttackHitbox();
}

AttackingState::~AttackingState()
{
	if (m_attackHitbox)
	{
		delete m_attackHitbox;
		m_attackHitbox = nullptr;
	}
}

void AttackingState::enter(Character& character)
{
	character.changeCurrentTexture(character.m_texturesActionName.at(m_attack), character.m_texturesNamePath.at(character.m_texturesActionName.at(m_attack)), false);
}

CharacterState* AttackingState::handleCondition(Character& character, const std::string& condition)
{
	if (condition == "IDLE")
	{
		return new IdleState{};
	}
	else if (condition == "HITTED" && m_attack != "Ultimate")
	{
		return new HittedState{ condition };
	}

	return nullptr;
}

void AttackingState::update(Character& character, float& deltaTime)
{
	character.m_velocity.x = 0.f;

	character.updateAttackHitbox(m_attackHitbox);

	if (character.m_animationEnd)
	{
		if (m_attack != "AirAttack")
		{
			character.setState(new IdleState{});
		}
		else
		{
			character.setState(new FallingState{});
		}
	}
}

bool AttackingState::checkAttack(Character& thisCharacter, Character& otherCharacter)
{
	if (m_attackHitbox->getShape().getGlobalBounds().intersects(otherCharacter.getShape().getGlobalBounds()))
	{
		if (otherCharacter.getStateName() != "HittedState")
		{
			if (!m_attackHitbox->getIsUltimateActivate())
			{
				if (thisCharacter.getEntityName() != "wind_hashashin")
				{
					otherCharacter.setState(new HittedState{ "HITTED", &thisCharacter });
				}
				else
				{
					if (dynamic_cast<WindHashashin*>(&thisCharacter)->getActivateUltimate())
					{
						otherCharacter.setState(new HittedState{ "FAST_HITTED", &thisCharacter });
					}
					else
					{
						otherCharacter.setState(new HittedState{ "HITTED", &thisCharacter });
					}
				}
				
				return true;
			}
			else
			{
				if (thisCharacter.getEntityName() == "wind_hashashin")
				{
					dynamic_cast<WindHashashin*>(&thisCharacter)->setActivateUltimate(true);

					otherCharacter.setShapePosition(thisCharacter.getShapePosition());
					otherCharacter.setSpritePosition(sf::Vector2f{ thisCharacter.getShapePosition().x, thisCharacter.getShapePosition().y - (thisCharacter.getSpriteSize().y - thisCharacter.getShapeSize().y) / 2.f });

					otherCharacter.setVelocity(sf::Vector2f{ 0.f, 0.f });

					return true;
				}
			}
		}
	}

	return false;
}
