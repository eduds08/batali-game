#include "HittedState.h"

#include "IdleState.h"
#include "DeadState.h"
#include "ProjectileEntity.h"
#include "Character.h"

HittedState::HittedState(const std::string& hittedMode, Character* attacker)
	: m_attacker{ attacker }
{
	m_stateName = "HittedState";

	if (hittedMode == "HITTED")
	{
		m_hittedMode = "Hitted";
	}
	else if (hittedMode == "FAST_HITTED")
	{
		m_hittedMode = "FastHit";
	}
}

void HittedState::enter(Character& character)
{
	character.changeCurrentTexture(character.m_texturesActionName.at(m_hittedMode), character.m_texturesNamePath.at(character.m_texturesActionName.at(m_hittedMode)), false);

	float attackDirection = m_attacker->getShapePosition().x - character.getShapePosition().x;

	if (m_attacker->getStateName() == "AttackingState")
	{
		character.m_hp -= m_attacker->getCharacterState<AttackingState>()->m_attackHitbox->getDamage();
	}
	else
	{
		if (dynamic_cast<ProjectileEntity*>(m_attacker) != nullptr)
		{
			if (dynamic_cast<ProjectileEntity*>(m_attacker)->getProjectiles().size() > 0)
				character.m_hp -= dynamic_cast<ProjectileEntity*>(m_attacker)->getProjectiles().at(0)->getDamage();
		}
	}

	std::cout << "hit\n---\n";

	if (attackDirection < 0.f)
	{
		// attack coming from left
		if (character.m_facingRight == 1)
		{
			character.m_facingRight = -1;
			character.flipSprite();
		}
	}
	else
	{
		// attack coming from right
		if (character.m_facingRight == -1)
		{
			character.m_facingRight = 1;
			character.flipSprite();
		}
	}
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
