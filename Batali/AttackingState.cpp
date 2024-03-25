#include "AttackingState.h"

#include "IdleState.h"

#include "Character.h"
#include "HittedState.h"
#include "JumpingState.h"
#include "FallingState.h"

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

	teste = new AttackHitbox();
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

	character.updateAttackHitbox(teste);

	if (character.m_animationEnd)
	{
		if (m_attack != "AirAttack")
		{
			//character.handleCondition("IDLE");
			character.setState(new IdleState{});
		}
		else
		{
			character.setState(new FallingState{});
		}
	}

	
}

void AttackingState::isCollidingWithEntity(Character& attackedCharacter)
{
	/*if (m_shape.getGlobalBounds().intersects(attackingEntity.getAttackHitbox().getShape().getGlobalBounds()))
	{
		return true;
	}*/

	if (teste->getShape().getGlobalBounds().intersects(attackedCharacter.getShape().getGlobalBounds()))
	{
		if (dynamic_cast<HittedState*>(attackedCharacter.getCharacterState()) == nullptr)
			attackedCharacter.setState(new HittedState{});
		//return true;
	}

	//Was attacked by Wind Hashashin's ultimate activate
	//if (attackingEntity.getEntityName() == "wind_hashashin")
	//{
	//	if (m_shape.getGlobalBounds().intersects(dynamic_cast<WindHashashin*>(&attackingEntity)->getUltimateActivateHitbox().getGlobalBounds()))
	//	{
	//		isUltimateActivate = true;
	//		dynamic_cast<WindHashashin*>(&attackingEntity)->setActivateUltimate(true);

	//		setShapePosition(attackingEntity.getShapePosition());
	//		setSpritePosition(sf::Vector2f{ getShapePosition().x, getShapePosition().y - (getSpriteSize().y - getShapeSize().y) / 2.f });

	//		setVelocity(sf::Vector2f{ 0.f, 0.f });

	//		return true;
	//	}
	//}

	//// Was attacked by projectiles
	//if (dynamic_cast<ProjectileEntity*>(&attackingEntity) != nullptr)
	//{
	//	for (auto& ultimateProjectile : dynamic_cast<ProjectileEntity*>(&attackingEntity)->getProjectiles())
	//	{
	//		if (m_shape.getGlobalBounds().intersects(ultimateProjectile->getShape().getGlobalBounds()))
	//		{
	//			ultimateProjectile->setCollided(true);

	//			return true;
	//		}
	//	}
	//}

	//return false;
}
