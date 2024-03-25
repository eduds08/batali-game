#include "AttackingState.h"

#include "IdleState.h"

#include "Character.h"
#include "HittedState.h"
#include "JumpingState.h"
#include "FallingState.h"

#include "ProjectileEntity.h"

#include "WindHashashin.h"

AttackingState::AttackingState(const std::string& attack)
{
	if (attack == "ATTACK_1")
	{
		m_attack = "Attack1";
	}
	if (attack == "ATTACK_2")
	{
		m_attack = "Attack2";
	}
	if (attack == "AIR_ATTACK")
	{
		m_attack = "AirAttack";
	}
	if (attack == "ULTIMATE")
	{
		m_attack = "Ultimate";
	}

	m_attackHitbox = new AttackHitbox();
}

AttackingState::~AttackingState()
{
	if (m_attackHitbox)
	{
		delete m_attackHitbox;
		m_attackHitbox = nullptr;
	}
}

void AttackingState::enter(Character& character)
{
	character.changeCurrentTexture(character.m_texturesActionName.at(m_attack), character.m_texturesNamePath.at(character.m_texturesActionName.at(m_attack)), false);
}

CharacterState* AttackingState::handleCondition(Character& character, const std::string& condition)
{
	if (condition == "IDLE")
	{
		return new IdleState{};
	}
	else if (condition == "HITTED" && m_attack != "Ultimate")
	{
		return new HittedState{};
	}

	return nullptr;
}

void AttackingState::update(Character& character, float& deltaTime)
{
	character.m_velocity.x = 0.f;

	character.updateAttackHitbox(m_attackHitbox);

	if (character.m_animationEnd)
	{
		if (m_attack != "AirAttack")
		{
			character.setState(new IdleState{});
		}
		else
		{
			character.setState(new FallingState{});
		}
	}
}

bool AttackingState::checkAttack(Character& thisCharacter, Character& otherCharacter)
{
	if (m_attackHitbox->getShape().getGlobalBounds().intersects(otherCharacter.getShape().getGlobalBounds()))
	{
		if (dynamic_cast<HittedState*>(otherCharacter.getCharacterState()) == nullptr)
		{
			if (!m_attackHitbox->getIsUltimateActivate())
			{
				//otherCharacter.setState(new HittedState{});
				return true;
			}
			else
			{
				if (thisCharacter.getEntityName() == "wind_hashashin")
				{
					dynamic_cast<WindHashashin*>(&thisCharacter)->setActivateUltimate(true);

					otherCharacter.setShapePosition(thisCharacter.getShapePosition());
					otherCharacter.setSpritePosition(sf::Vector2f{ thisCharacter.getShapePosition().x, thisCharacter.getShapePosition().y - (thisCharacter.getSpriteSize().y - thisCharacter.getShapeSize().y) / 2.f });

					otherCharacter.setVelocity(sf::Vector2f{ 0.f, 0.f });

					return true;
				}
			}
		}
	}
	else
	{
		// Was attacked by projectiles
		if (dynamic_cast<ProjectileEntity*>(&thisCharacter) != nullptr)
		{
			for (auto& ultimateProjectile : dynamic_cast<ProjectileEntity*>(&thisCharacter)->getProjectiles())
			{
				if (ultimateProjectile->getShape().getGlobalBounds().intersects(otherCharacter.getShape().getGlobalBounds()))
				{
					ultimateProjectile->setCollided(true);
					//otherCharacter.setState(new HittedState{});
					return true;
				}
			}
		}
	}

	return false;
}

// If attackDirection is negative, the attack came from the right. Otherwise, it came from left.
//float attackDirection = attackingEntity.getShapePosition().x - attackedEntity.getShapePosition().x;

//if (!isUltimateActivate)
//{
	//bool gotHit = attackedEntity.takeDamage(m_deltaTime, attackDirection, attackingEntity.getAttackHitbox().getDamage());

	//if (gotHit && attackingEntity.getAttackHitbox().getDamage() != WIND_HASHASHIN_ULTIMATE_DAMAGE)
	//{
	//	// Knockback of the attackedEntity. The attackedEntity will be pushed until it doesn't collide with the hitbox anymore or until it collides with a wall. It's not pushed if attacked entity is on roll. 
	//	while (attackedEntity.getShape().getGlobalBounds().intersects((attackingEntity.getAttackHitbox().getShape().getGlobalBounds())) && !attackedEntity.getIsCollidingHorizontally() /*&& !attackedEntity.getOnRoll()*/)
	//	{
	//		for (auto& ground : m_grounds)
	//		{
	//			updateEntityCollisionWithGrounds(attackedEntity, ground);
	//		}
	//		attackedEntity.knockbackMove(m_deltaTime, attackDirection);
	//	}
	//}
//}