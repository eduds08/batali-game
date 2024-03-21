#include "RunningState.h"

#include "JumpingState.h"
#include "RollingState.h"
#include "OnUltimateState.h"
#include "IdleState.h"

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

	}
	else if (condition == "ULTIMATE")
	{
		return new OnUltimateState{};
	}
	else if (condition == "IDLE")
	{
		return new IdleState{};
	}

	return nullptr;
}

void RunningState::update(Character& character, float& deltaTime)
{
	character.m_velocity.x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
	{
		character.m_facingRight = -1;
		character.m_velocity.x -= character.m_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
	{
		character.m_facingRight = 1;
		character.m_velocity.x += character.m_speed;
	}

	character.flipSprite();

	character.m_velocity.y += GRAVITY * deltaTime;

	if (character.m_velocity.x == 0.f)
	{
		character.handleCondition("IDLE");
	}
}
