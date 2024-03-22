#include "RunningState.h"

#include "JumpingState.h"
#include "RollingState.h"
#include "OnUltimateState.h"
#include "IdleState.h"
#include "FallingState.h"
#include "AttackingState.h"
#include "HittedState.h"

#include "Character.h"

RunningState::RunningState()
{

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
	else if (condition == "ATTACK_1" || condition == "ATTACK_2")
	{
		return new AttackingState{ condition };
	}
	else if (condition == "ULTIMATE")
	{
		return new OnUltimateState{};
	}
	else if (condition == "IDLE")
	{
		return new IdleState{};
	}
	else if (condition == "FALL")
	{
		return new FallingState{};
	}
	else if (condition == "HITTED")
	{
		return new HittedState{};
	}

	return nullptr;
}

void RunningState::update(Character& character, float& deltaTime)
{
	character.m_velocity.y += GRAVITY * deltaTime;

	if (character.m_velocity.x == 0.f)
	{
		character.handleCondition("IDLE");
	}
}
