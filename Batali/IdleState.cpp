#include "IdleState.h"

#include "JumpingState.h"
#include "RollingState.h"
#include "OnUltimateState.h"
#include "RunningState.h"

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

	}
	else if (condition == "ULTIMATE")
	{
		return new OnUltimateState{};
	}
	else if (condition == "RUN")
	{
		return new RunningState{};
	}

    return nullptr;
}

void IdleState::update(Character& character)
{
}
