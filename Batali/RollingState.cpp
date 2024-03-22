#include "RollingState.h"

#include "IdleState.h"
#include "Character.h"

void RollingState::enter(Character& character)
{
	character.changeCurrentTexture(character.m_texturesActionName.at("Roll"), character.m_texturesNamePath.at(character.m_texturesActionName.at("Roll")), false);
}

CharacterState* RollingState::handleCondition(Character& character, const std::string& condition)
{
	if (condition == "IDLE")
	{
		return new IdleState{};
	}

	return nullptr;
}

void RollingState::update(Character& character, float& deltaTime)
{
	character.m_velocity.x += (character.m_facingRight * m_rollSpeed);

	if (character.m_animationEnd)
	{
		//character.handleCondition("IDLE");
		character.setState(new IdleState{});
	}
}
