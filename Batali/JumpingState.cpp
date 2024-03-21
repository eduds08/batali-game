#include "JumpingState.h"

#include "IdleState.h"
#include "FallingState.h"

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
	else if (condition == "FALL")
	{
		return new FallingState{};
	}

    return nullptr;
}

void JumpingState::update(Character& character, float& deltaTime)
{
	//character.m_velocity.x = 0.f;

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
	{
		character.m_facingRight = -1;
		character.m_velocity.x -= character.m_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
	{
		character.m_facingRight = 1;
		character.m_velocity.x += character.m_speed;
	}*/

	//character.flipSprite();

	if (character.m_velocity.y > 0.f)
	{
		character.handleCondition("FALL");
	}
}
