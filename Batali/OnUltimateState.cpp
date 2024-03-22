#include "OnUltimateState.h"

#include "IdleState.h"

#include "Character.h"

void OnUltimateState::enter(Character& character)
{
    character.changeCurrentTexture(character.m_texturesActionName.at("Ultimate"), character.m_texturesNamePath.at(character.m_texturesActionName.at("Ultimate")), false);
}

CharacterState* OnUltimateState::handleCondition(Character& character, const std::string& condition)
{
	if (condition == "IDLE")
	{
		return new IdleState{};
	}

    return nullptr;
}

void OnUltimateState::update(Character& character, float& deltaTime)
{
	character.m_velocity.x = 0.f;

	character.updateAttackHitbox();

	if (character.m_animationEnd)
	{
		//character.handleCondition("IDLE");
		character.setState(new IdleState{});
	}
}
