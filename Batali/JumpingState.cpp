#include "JumpingState.h"

#include "IdleState.h"

#include "Character.h"

void JumpingState::enter(Character& character)
{
	character.changeCurrentTexture(character.m_texturesActionName.at("Jumping"), character.m_texturesNamePath.at(character.m_texturesActionName.at("Jumping")), true);
	character.m_velocity.y = -1 * sqrt(2.f * GRAVITY * m_jumpHeight);
}

CharacterState* JumpingState::handleCondition(Character& character, const std::string& condition)
{
	if (condition == "ATTACK_1" || condition == "ATTACK_2")
	{

	}
	else if (condition == "IDLE")
	{
		return new IdleState{};
	}

    return nullptr;
}

void JumpingState::update(Character& character, float& deltaTime)
{
	if (!m_onFall && character.m_velocity.y > 0.f)
	{
		m_onFall = true;
	}

	if (m_onFall && character.m_currentTexture == character.m_entityName + "Jumping")
	{
		character.changeCurrentTexture(character.m_texturesActionName.at("Falling"), character.m_texturesNamePath.at(character.m_texturesActionName.at("Falling")), true);
	}

	if (m_onFall)
	{
		if (character.m_velocity.y == 0.f || character.m_collisionDirection.y < 0.f)
		{
			character.handleCondition("IDLE");
		}
	}
}
