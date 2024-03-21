#include "IdleState.h"

#include "JumpingState.h"
#include "RollingState.h"
#include "OnUltimateState.h"
#include "RunningState.h"

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

void IdleState::update(Character& character, float& deltaTime)
{
	character.m_velocity.x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
	{
		character.handleCondition("RUN");
	}
}
