#include "SwordEntity.h"

SwordEntity::SwordEntity()
	: DamageEntity{}
{
}

void SwordEntity::updateAttack(bool attackCondition1, bool attackCondition2, bool ultimateCondition)
{
	if (attackCondition1 && m_canJump && m_attackMode == "off" && !m_onRoll && !ultimateCondition && !m_onWindHashashinUltimate)
	{
		m_attackMode = "onAttack1";
	}
	else if (attackCondition2 && m_canJump && m_attackMode == "off" && !m_onRoll && !ultimateCondition && !m_onWindHashashinUltimate)
	{
		m_attackMode = "onAttack2";
	}
	else if ((attackCondition1 || attackCondition2) && !m_canJump && m_attackMode == "off" && !m_onRoll && !ultimateCondition && !m_onWindHashashinUltimate)
	{
		m_attackMode = "onAirAttack";
	}
	else if (ultimateCondition && m_canJump && m_attackMode == "off" && !m_onRoll && m_remainingManaToUltimate <= 0 && !m_onWindHashashinUltimate)
	{
		m_attackMode = "onUltimate";

		m_remainingManaToUltimate = 5;
	}

	if (m_attackMode != "off")
	{
		if (m_attackMode != "onAirAttack")
		{
			// Don't let the entity move if it is attacking on ground
			m_velocity.x = 0.f;
			m_velocity.y = 0.f;

			// Stop the attack when attack animation ends (and also stores the current animation as the previous one so the next attack uses the other attacking animation) or when entity gets hitted
			if (((m_currentTexture == m_entityName + "Attack1" || m_currentTexture == m_entityName + "Attack2" || m_currentTexture == m_entityName + "Ultimate") && m_animationEnd) || m_inDamageCooldown == true)
			{
				m_attackMode = "off";

				//m_activateUltimate = false;
			}
		}
		else
		{
			m_velocity.x = 0.f;

			if ((m_currentTexture == m_entityName + "AirAttack" && m_animationEnd) || m_inDamageCooldown == true || (m_canJump && m_currentTexture == m_entityName + "Falling"))
			{
				m_attackMode = "off";
			}
		}
	}

	updateAttackHitbox();
}

void SwordEntity::updateSwordEntity(float& deltaTime)
{
	// Only sets dead = true when the dead animation ends, that way we can still call updateAnimation() even if hp <= 0
	if (this->m_currentTexture == this->m_texturesActionName.at("Death") && !this->m_dead && this->m_animationEnd)
	{
		this->die();
	}

	this->m_remainingManaToUltimate = 0;

	// Only called if hp > 0
	if (!this->m_dying)
	{
		this->updateMovement(this->m_conditionRunLeft, this->m_conditionRunRight, this->m_conditionJump, deltaTime, this->m_conditionRoll);

		this->updateAttack(this->m_conditionAttack1, this->m_conditionAttack2, this->m_conditionUltimate);

		this->updateDamage();

		this->move(deltaTime);
	}

	// Entity is dying (still playing dying animation)
	if (!this->m_dead)
	{
		// If the entity is dying (not dead yet), it doesn't move anymore, so we call this method to move it in y-direction and avoids it floating in the air after death
		if (this->m_dying)
		{
			this->m_velocity.x = 0.f;
			this->m_velocity.y += GRAVITY * deltaTime;
			this->move(deltaTime);
		}

		this->updateLimits();
	}
}
