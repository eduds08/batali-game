#include "IdleState.h"

#include "JumpingState.h"
#include "RollingState.h"
#include "OnUltimateState.h"
#include "RunningState.h"
#include "FallingState.h"
#include "AttackingState.h"

#include "Character.h"

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
	else if (condition == "ATTACK_1" || condition == "ATTACK_2")
	{
		return new AttackingState{ condition };
	}
	else if (condition == "ULTIMATE")
	{
		return new OnUltimateState{};
	}
	else if (condition == "RUN")
	{
		return new RunningState{};
	}
	else if (condition == "FALL")
	{
		return new FallingState{};
	}


    return nullptr;
}

void IdleState::update(Character& character, float& deltaTime)
{

}
