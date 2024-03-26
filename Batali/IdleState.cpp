#include "IdleState.h"

#include "JumpingState.h"
#include "RollingState.h"
#include "RunningState.h"
#include "FallingState.h"
#include "AttackingState.h"
#include "HittedState.h"

#include "Character.h"

IdleState::IdleState()
{
	m_stateName = "IdleState";
}

void IdleState::enter(Character& character)
{
	character.changeCurrentTexture(character.m_texturesActionName.at("Idle"), character.m_texturesNamePath.at(character.m_texturesActionName.at("Idle")), true);
}

CharacterState* IdleState::handleCondition(Character& character, const std::string& condition)
{
	if (condition == "JUMP")
	{
		return new JumpingState{};
	}
	else if (condition == "ROLL")
	{
		return new RollingState{};
	}
	else if (condition == "ATTACK_1" || condition == "ATTACK_2" || condition == "ULTIMATE")
	{
		return new AttackingState{ condition };
	}
	else if (condition == "RUN")
	{
		return new RunningState{};
	}
	else if (condition == "FALL")
	{
		return new FallingState{};
	}
	else if (condition == "HITTED" || condition == "FAST_HITTED")
	{
		return new HittedState{ condition };
	}


    return nullptr;
}

void IdleState::update(Character& character, float& deltaTime)
{
}
