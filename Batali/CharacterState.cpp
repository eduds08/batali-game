#include "CharacterState.h"
#include "Character.h"

void CharacterState::updateHorizontalMovement(Character& character)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) && character.getPlayerNumber() == 1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left) && character.getPlayerNumber() == 2))
	{
		character.m_facingRight = -1;
		character.m_velocity.x -= character.m_speed;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) && character.getPlayerNumber() == 1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right) && character.getPlayerNumber() == 2))
	{
		character.m_facingRight = 1;
		character.m_velocity.x += character.m_speed;
	}

	character.flipSprite();
}
