#include "FallingState.h"

#include "IdleState.h"

#include "Character.h"

void FallingState::enter(Character& character)
{
 	character.changeCurrentTexture(character.m_texturesActionName.at("Falling"), character.m_texturesNamePath.at(character.m_texturesActionName.at("Falling")), true);
}

CharacterState* FallingState::handleCondition(Character& character, const std::string& condition)
{
	if (condition == "IDLE")
	{
		return new IdleState{};
	}

	return nullptr;
}

void FallingState::update(Character& character, float& deltaTime)
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

	if (character.m_velocity.y == 0.f || character.m_collisionDirection.y < 0.f)
	{
		character.handleCondition("IDLE");
	}
}
