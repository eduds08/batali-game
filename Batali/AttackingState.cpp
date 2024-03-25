#include "AttackingState.h"

#include "IdleState.h"

#include "Character.h"
#include "HittedState.h"
#include "JumpingState.h"
#include "FallingState.h"

AttackingState::AttackingState(const std::string& attack)
{
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

	teste = new AttackHitbox();
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
		return new HittedState{};
	}
	
	return nullptr;
}

void AttackingState::update(Character& character, float& deltaTime)
{
	character.m_velocity.x = 0.f;

	character.updateAttackHitbox(teste);

	if (character.m_animationEnd)
	{
		if (m_attack != "AirAttack")
		{
			//character.handleCondition("IDLE");
			character.setState(new IdleState{});
		}
		else
		{
			character.setState(new FallingState{});
		}
	}

	
}
