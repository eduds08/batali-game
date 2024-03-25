#include "HittedState.h"

#include "IdleState.h"
#include "DeadState.h"

#include "Character.h"

void HittedState::enter(Character& character)
{
	//character.m_hp -= damage;
	character.m_hp -= 100;

	std::cout << "hit\n---\n";

	/*if (m_remainingManaToUltimate > 0)
	{
		--m_remainingManaToUltimate;
	}*/

	//if (attackDirection < 0.f)
	//{
	//	// attack coming from left
	//	if (m_facingRight == 1)
	//	{
	//		m_facingRight = -1;
	//		MovableEntity::flipSprite();
	//	}
	//}
	//else
	//{
	//	// attack coming from right
	//	if (m_facingRight == -1)
	//	{
	//		m_facingRight = 1;
	//		MovableEntity::flipSprite();
	//	}
	//}

	//handleCondition("HITTED");

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
	// lógica para não tomar dano (ou fora daqui)

	//character.m_knockbackVelocity = KNOCKBACK_SPEED;

	if (character.m_animationEnd)
	{
		if (character.m_hp <= 0)
		{
			//character.handleCondition("DEAD");
			character.setState(new DeadState{});
		}
		else
		{
			//character.handleCondition("IDLE");
			character.setState(new IdleState{});
		}
	}
}
