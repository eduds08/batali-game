#pragma once

#include "ColliderEntity.h"
#include "CharacterState.h"
#include "AttackHitbox.h"
#include "AttackingState.h"

class Character : public ColliderEntity
{
public:
	Character();
	virtual ~Character();

	void handleCondition(const std::string& condition);

	virtual void update(float& deltaTime);
	
	void setState(CharacterState* state);

	virtual void updateAttackHitbox(AttackHitbox* m_attackHitbox) = 0;

	bool isCollidingWithAttack(Character& attackingEntity, bool& isUltimateActivate);


	void render(sf::RenderWindow& window)
	{
		window.draw(m_sprite);
		if (m_state != nullptr)
		{
			if (dynamic_cast<AttackingState*>(m_state) != nullptr && dynamic_cast<AttackingState*>(m_state)->teste != nullptr)
			{
				window.draw(dynamic_cast<AttackingState*>(m_state)->teste->getShape());
			}
		}
		
	}

	//const AttackHitbox& getAttackHitbox() const { return m_attackHitbox; }

	//const sf::RectangleShape& getAttackHitbox() const { return m_attackHitbox.getShape(); }
	/*const int getDamage() const { return m_damage; }*/

	// Updates entity's attributes when it gets attacked (and returns if attackedEntity got hit or not)
	bool takeDamage(float& deltaTime, float attackDirection, int damage);

	// Moves the entity after being hit. attackDirection -> direction of the attack (from left or right)
	void knockbackMove(float& deltaTime, float attackDirection);

	const int* getHp() const { return &m_hp; }
	const int* getRemainingManaToUltimate() const { return &m_remainingManaToUltimate; }
	//const int* getStamina() const { return &m_stamina; }

	virtual const int getPlayerNumber() const { return -1; }

	friend class RollingState;
	friend class RunningState;
	friend class JumpingState;
	friend class FallingState;
	friend class IdleState;
	friend class AttackingState;
	friend class OnUltimateState;
	friend class HittedState;
	friend class DeadState;

protected:
	CharacterState* m_state{ nullptr };

	//AttackHitbox m_attackHitbox{};
	
	int m_remainingManaToUltimate{ 5 };
	
	/*sf::Clock m_staminaRecoverClock{};
	int m_stamina{ 100 };
	float m_staminaRecoverTime{};*/
	

	int m_hp{ 1300 };
};
