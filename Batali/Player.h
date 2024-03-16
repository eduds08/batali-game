#pragma once

#include "ProjectileEntity.h"

template <class T>
class Player : public T
{
public:
	Player(sf::Vector2f firstPosition, int playerNumber=1);
	~Player();

	// Main character's update
	void update(float& deltaTime);

	// Changes the current texture based upon the entity's current activity (jumping, running, attacking, etc...). Called inside updateAnimation()
	void updateTexture();

	/* Setters */

	

	/* Getters */

	const int getPlayerNumber() const { return m_playerNumber; }

private:
	int m_playerNumber{ 1 };
};

template<class T>
inline Player<T>::Player(sf::Vector2f firstPosition, int playerNumber)
	: T{ firstPosition }
	, m_playerNumber{ playerNumber }
{
	// Second player starts facing left
	if (this->m_playerNumber == 2)
	{
		this->m_facingRight = -1;
		this->flipSprite();
	}
}

template<class T>
inline Player<T>::~Player()
{
}

template<class T>
inline void Player<T>::update(float& deltaTime)
{
	this->updateCharacter(deltaTime);

	//// Only sets dead = true when the dead animation ends, that way we can still call updateAnimation() even if hp <= 0
	//if (this->m_currentTexture == this->m_texturesActionName.at("Death") && !this->m_dead && this->m_animationEnd)
	//{
	//	this->die();
	//}

	//this->m_remainingManaToUltimate = 0;

	//// Only called if hp > 0
	//if (!this->m_dying)
	//{
	//	this->updateMovement(this->m_conditionRunLeft, this->m_conditionRunRight, this->m_conditionJump, deltaTime, this->m_conditionRoll);

	//	this->updateAttack(this->m_conditionAttack1, this->m_conditionAttack2, this->m_conditionUltimate);

	//	this->updateDamage();

	//	this->move(deltaTime);
	//}

	//// Entity is dying (still playing dying animation)
	//if (!this->m_dead)
	//{
	//	// If the entity is dying (not dead yet), it doesn't move anymore, so we call this method to move it in y-direction and avoids it floating in the air after death
	//	if (this->m_dying)
	//	{
	//		this->m_velocity.x = 0.f;
	//		this->m_velocity.y += GRAVITY * deltaTime;
	//		this->move(deltaTime);
	//	}

	//	this->updateLimits();
	//}
}

template<class T>
inline void Player<T>::updateTexture()
{
	if (this->m_dying)
	{
		this->changeCurrentTexture(this->m_texturesActionName.at("Death"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Death")), false);
	}
	else if (this->m_hitted)
	{
		this->m_onWindHashashinUltimate ? this->changeCurrentTexture(this->m_texturesActionName.at("_HitOnWindHashashinUltimate"), this->m_texturesNamePath.at(this->m_texturesActionName.at("_HitOnWindHashashinUltimate")), false) : this->changeCurrentTexture(this->m_texturesActionName.at("Hitted"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Hitted")), false);
	}
	else if (this->m_velocity.y != 0.f && !this->m_canJump)
	{
		if (this->m_attackMode == "onAirAttack")
		{
			this->changeCurrentTexture(this->m_texturesActionName.at("AirAttack"), this->m_texturesNamePath.at(this->m_texturesActionName.at("AirAttack")), false);
		}
		else
		{
			this->m_velocity.y > 0.f ? this->changeCurrentTexture(this->m_texturesActionName.at("Falling"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Falling")), true) : this->changeCurrentTexture(this->m_texturesActionName.at("Jumping"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Jumping")), true);;
		}
	}
	else if (this->m_attackMode == "off")
	{
		if (this->m_onRoll)
		{
			this->changeCurrentTexture(this->m_texturesActionName.at("Roll"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Roll")), false);
		}
		else
		{
			this->m_isRunning ? this->changeCurrentTexture(this->m_texturesActionName.at("Running"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Running")), true) : this->changeCurrentTexture(this->m_texturesActionName.at("Idle"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Idle")), true);
		}
	}
	else if (this->m_attackMode != "off")
	{
		if (this->m_attackMode == "onUltimate")
		{
			this->changeCurrentTexture(this->m_texturesActionName.at("Ultimate"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Ultimate")), false);
		}
		else if (this->m_attackMode != "onAirAttack")
		{
			if (this->m_attackMode == "onAttack1")
			{
				this->changeCurrentTexture(this->m_texturesActionName.at("Attack1"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Attack1")), false);
			}
			else if (this->m_attackMode == "onAttack2")
			{
				this->changeCurrentTexture(this->m_texturesActionName.at("Attack2"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Attack2")), false);
			}
		}
	}
}
