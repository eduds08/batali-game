#include "HittedState.h"

#include "IdleState.h"
#include "DeadState.h"

#include "Character.h"

HittedState::HittedState()
{
}

void HittedState::enter(Character& character)
{
	character.changeCurrentTexture(character.m_texturesActionName.at("Hitted"), character.m_texturesNamePath.at(character.m_texturesActionName.at("Hitted")), false);
}

CharacterState* HittedState::handleCondition(Character& character, const std::string& condition)
{
	if (condition == "DEAD")
	{
		return new DeadState{};
	}
	else if (condition == "IDLE")
	{
		return new IdleState{};
	}

	return nullptr;
}

void HittedState::update(Character& character, float& deltaTime)
{
	if (character.m_animationEnd)
	{
		if (character.m_hp <= 0)
		{
			character.setState(new DeadState{});
		}
		else
		{
			character.setState(new IdleState{});
		}
	}
}
