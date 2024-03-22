#include "AttackingState.h"

#include "IdleState.h"

#include "Character.h"
#include "HittedState.h"

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
	else if (condition == "HITTED")
	{
		return new HittedState{};
	}
	
	return nullptr;
}

void AttackingState::update(Character& character, float& deltaTime)
{
	character.m_velocity.x = 0.f;

	if (character.m_animationEnd)
	{
		character.handleCondition("IDLE");
	}

	character.updateAttackHitbox();
}
