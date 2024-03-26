#include "RunningState.h"

#include "JumpingState.h"
#include "RollingState.h"
#include "IdleState.h"
#include "FallingState.h"
#include "AttackingState.h"
#include "HittedState.h"

#include "Character.h"

RunningState::RunningState()
{
	m_stateName = "RunningState";
}

void RunningState::enter(Character& character)
{
	character.changeCurrentTexture(character.m_texturesActionName.at("Running"), character.m_texturesNamePath.at(character.m_texturesActionName.at("Running")), true);
}

CharacterState* RunningState::handleCondition(Character& character, const std::string& condition)
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
	else if (condition == "IDLE")
	{
		return new IdleState{};
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

void RunningState::update(Character& character, float& deltaTime)
{
	character.m_velocity.y += GRAVITY * deltaTime;

	updateHorizontalMovement(character);

	if (character.m_velocity.x == 0.f)
	{
		character.setState(new IdleState{});
	}
}
