#include "JumpingState.h"

#include "IdleState.h"
#include "FallingState.h"
#include "HittedState.h"
#include "AttackingState.h"

#include "Character.h"

JumpingState::JumpingState()
{
	m_stateName = "JumpingState";
}

void JumpingState::enter(Character& character)
{
	character.changeCurrentTexture(character.m_texturesActionName.at("Jumping"), character.m_texturesNamePath.at(character.m_texturesActionName.at("Jumping")), true);
	character.m_velocity.y = -1 * sqrt(2.f * GRAVITY * m_jumpHeight);
}

CharacterState* JumpingState::handleCondition(Character& character, const std::string& condition)
{
	if (condition == "ATTACK_1" || condition == "ATTACK_2")
	{
		return new AttackingState{ "AIR_ATTACK" };
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

void JumpingState::update(Character& character, float& deltaTime)
{
	updateHorizontalMovement(character);

	if (character.m_velocity.y > 0.f)
	{
		character.setState(new FallingState{});
	}
	else if (character.m_collisionDirection.y > 0.f && character.m_velocity.y == 0.f)
	{
		character.setState(new IdleState{});
	}
}
