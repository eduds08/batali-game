//#include "DamageEntity.h"
//#include "WindHashashin.h"
//#include "ProjectileEntity.h"
//
//DamageEntity::DamageEntity()
//	: WalkingEntity{}
//{
//}
//
//void DamageEntity::updateDamage()
//{
//	// handleCollision() is called after this, so if the entity collides with a wall, knockback is set to 0
//	m_knockbackVelocity = KNOCKBACK_SPEED;
//
//	// Makes sure the Hitted animation is only played once per attack
//	if (m_hitted && m_animationEnd)
//	{
//		m_hitted = false;
//
//		if (m_hp <= 0)
//		{
//			m_dying = true;
//		}
//	}
//
//	if (m_currentTexture != m_entityName + "Hitted" && m_currentTexture != m_entityName + "FastHit")
//	{
//		m_inDamageCooldown = false;
//	}
//}
//
//bool DamageEntity::takeDamage(float& deltaTime, float attackDirection, int damage)
//{
//	// Only executed if not already dead and when not immune (on damageCooldown or onRoll)
//	if (!m_inDamageCooldown && !m_hitted && !m_dying && !m_onRoll && getAttackMode() != "onUltimate")
//	{
//		m_inDamageCooldown = true;
//		m_hitted = true;
//
//		m_hp -= damage;
//
//		std::cout << "hit\n---\n";
//
//		if (m_remainingManaToUltimate > 0)
//		{
//			--m_remainingManaToUltimate;
//		}
//
//		if (attackDirection < 0.f)
//		{
//			// attack coming from left
//			if (m_facingRight == 1)
//			{
//				m_facingRight = -1;
//				flipSprite();
//			}
//		}
//		else
//		{
//			// attack coming from right
//			if (m_facingRight == -1)
//			{
//				m_facingRight = 1;
//				flipSprite();
//			}
//		}
//
//		return true;
//	}
//
//	return false;
//}
//
//void DamageEntity::knockbackMove(float& deltaTime, float attackDirection)
//{
//	if (attackDirection < 0.f)
//	{
//		// attack coming from left
//			m_shape.move(sf::Vector2f{ m_knockbackVelocity, 0.f } *deltaTime);
//		}
//		else
//		{
//		// attack coming from right
//			m_shape.move(sf::Vector2f{ m_knockbackVelocity * -1.f, 0.f } *deltaTime);
//		}
//			
//	m_sprite.setPosition(sf::Vector2f{ getShapePosition().x, getShapePosition().y - (m_spriteHeight - getShapeSize().y) / 2.f });
//}
//
//void DamageEntity::die()
//{
//	m_dead = true;
//	resetAttackHitbox();
//	m_velocity.x = 0.f;
//	m_velocity.y = 0.f;
//}
//
//bool DamageEntity::isCollidingWithAttack(SwordEntity& attackingEntity, bool& isUltimateActivate)
//{
//	if (!m_dying)
//	{
//		if (m_shape.getGlobalBounds().intersects(attackingEntity.getAttackHitbox().getGlobalBounds()))
//		{
//			if (attackingEntity.getEntityName() != "wind_hashashin" && attackingEntity.getAttackMode() != "onUltimate")
//				m_onFastHit = false;
//			return true;
//		}
//
//		// Was attacked by Wind Hashashin's ultimate activate
//		if (attackingEntity.getEntityName() == "wind_hashashin")
//		{
//			if (m_shape.getGlobalBounds().intersects(dynamic_cast<WindHashashin*>(&attackingEntity)->getUltimateActivateHitbox().getGlobalBounds()))
//			{
//				isUltimateActivate = true;
//				m_onFreeze = true;
//				m_onFastHit = true;
//				dynamic_cast<WindHashashin*>(&attackingEntity)->setActivateUltimate(true);
//
//				setShapePosition(attackingEntity.getShapePosition());
//				setSpritePosition(sf::Vector2f{ getShapePosition().x, getShapePosition().y - (getSpriteSize().y - getShapeSize().y) / 2.f });
//
//				setVelocity(sf::Vector2f{ 0.f, 0.f });
//
//				return true;
//			}
//		}
//
//		// Was attacked by projectiles
//		if (dynamic_cast<ProjectileEntity*>(&attackingEntity) != nullptr)
//		{
//			for (auto& ultimateProjectile : dynamic_cast<ProjectileEntity*>(&attackingEntity)->getProjectiles())
//			{
//				if (m_shape.getGlobalBounds().intersects(ultimateProjectile->getShape().getGlobalBounds()))
//				{
//					ultimateProjectile->setCollided(true);
//					m_onFastHit = true;
//
//					return true;
//				}
//			}
//		}
//	}
//
//	return false;
//}
