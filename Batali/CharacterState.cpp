#include "CharacterState.h"
#include "Character.h"

void CharacterState::updateHorizontalMovement(Character& character)
{
	/*if (sf::Keyboard::isKeyPressed(character.getInputHandler().getRunLeftCommand().button))
	{
		character.m_facingRight = -1;
		character.m_velocity.x -= character.m_speed;
	}
	else if (sf::Keyboard::isKeyPressed(character.getInputHandler().getRunRightCommand().button))
	{
		character.m_facingRight = 1;
		character.m_velocity.x += character.m_speed;
	}*/

	character.flipSprite();
}
