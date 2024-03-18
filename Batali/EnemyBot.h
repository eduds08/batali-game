#pragma once

template <class T>
class EnemyBot : public T
{
public:
	EnemyBot(sf::Vector2f firstPosition, const sf::Vector2f& playerShapePosition, const sf::Vector2f& playerShapeSize);
	~EnemyBot();

	// Main character's update
	void update(float& deltaTime);

	// Changes the current texture based upon the entity's current activity (jumping, running, attacking, etc...). Called inside updateAnimation()
	void updateTexture();

private:
	// Alters attacks between one another
	std::string m_previousAttackingAnimation{};

	// Timer used to create a interval between attacks
	sf::Clock m_timeBetweenAttacksClock{};
	float m_timeBetweenAttacks{};

	const sf::Vector2f& m_playerShapePosition{};
	const sf::Vector2f& m_playerShapeSize{};
	float m_distanceFromPlayer{ ENEMY_DISTANCE_FROM_PLAYER  };
};

template<class T>
inline EnemyBot<T>::EnemyBot(sf::Vector2f firstPosition, const sf::Vector2f& playerShapePosition, const sf::Vector2f& playerShapeSize)
	: T{ firstPosition }
	, m_playerShapePosition{ playerShapePosition }
	, m_playerShapeSize{ playerShapeSize }
{
	this->m_facingRight = -1;
	this->flipSprite();

	this->m_speed = ENEMY_SPEED;

	m_previousAttackingAnimation = this->m_entityName + "Attack2";
}

template<class T>
inline EnemyBot<T>::~EnemyBot()
{
}

template<class T>
inline void EnemyBot<T>::update(float& deltaTime)
{
	// Only called if hp > 0
	if (!this->m_dying)
	{
		this->m_conditionRunLeft = m_playerShapePosition.x < this->getShapePosition().x - m_distanceFromPlayer;
		this->m_conditionRunRight = m_playerShapePosition.x > this->getShapePosition().x + m_distanceFromPlayer;
		this->m_conditionJump = (((m_playerShapePosition.y - m_playerShapeSize.y / 2.f) < (this->getShapePosition().y - this->getShapeSize().y / 2.f)) && this->m_isCollidingHorizontally);

		m_timeBetweenAttacks = m_timeBetweenAttacksClock.getElapsedTime().asSeconds();
		this->m_conditionAttack1 = (this->m_velocity.x == 0.f && m_timeBetweenAttacks > TIME_BETWEEN_ENEMY_ATTACKS) && m_previousAttackingAnimation == this->m_entityName + "Attack2";
		this->m_conditionAttack2 = (this->m_velocity.x == 0.f && m_timeBetweenAttacks > TIME_BETWEEN_ENEMY_ATTACKS) && m_previousAttackingAnimation == this->m_entityName + "Attack1";

		this->m_conditionRoll = false;
	}

	if (this->m_conditionAttack1)
	{
		m_previousAttackingAnimation = this->m_entityName + "Attack1";
	}
	else if (this->m_conditionAttack2)
	{
		m_previousAttackingAnimation = this->m_entityName + "Attack2";
	}

	T::update(deltaTime);

	if (this->m_attackMode != "off")
	{
		m_timeBetweenAttacksClock.restart();
		m_timeBetweenAttacks = 0.f;
	}
}

template<class T>
inline void EnemyBot<T>::updateTexture()
{
	if (this->m_dying)
	{
		this->changeCurrentTexture(this->m_texturesActionName.at("Dying"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Dying")), false);
	}
	else if (this->m_hitted)
	{
		this->m_onFreeze ? this->changeCurrentTexture(this->m_texturesActionName.at("FastHit"), this->m_texturesNamePath.at(this->m_texturesActionName.at("FastHit")), false) : this->changeCurrentTexture(this->m_texturesActionName.at("Hitted"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Hitted")), false);
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
			m_previousAttackingAnimation == this->m_entityName + "Attack1" ? this->changeCurrentTexture(this->m_texturesActionName.at("Attack2"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Attack2")), false) : this->changeCurrentTexture(this->m_texturesActionName.at("Attack1"), this->m_texturesNamePath.at(this->m_texturesActionName.at("Attack1")), false);
		}
	}
}
