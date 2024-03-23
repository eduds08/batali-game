//#pragma once
//
//#include "ColliderEntity.h"
//
//class WalkingEntity : public ColliderEntity
//{
//public:
//	WalkingEntity();
//	virtual ~WalkingEntity() = default;
//
//	
//
//	// Updates MovableEntity's m_velocity. Called before move()
//	void updateMovement(bool conditionRunLeft, bool conditionRunRight, bool conditionJump, float& deltaTime, bool conditionRoll = false);
//
//	/* Getters */
//
//	const bool getOnRoll() const { return m_onRoll; }
//	const int* getStamina() const { return &m_stamina; }
//
//	/* Pure Virtual Methods */
//
//	virtual const bool getHitted() const = 0;
//	virtual void setKnockbackVelocity(float knockbackVelocity) = 0;
//	virtual const bool getOnFreeze() const = 0;
//	virtual const std::string& getAttackMode() const = 0;
//
//	// Temporary
//	//friend class RollingState;
//
//protected:
//	bool m_conditionRunLeft{ false };
//	bool m_conditionRunRight{ false };
//	bool m_conditionJump{ false };
//	bool m_conditionRoll{ false };
//
//	bool m_canJump{ false };
//	bool m_isRunning{ false };
//	bool m_onRoll{ false };
//
//	float m_rollSpeed{};
//
//	float m_jumpHeight{};
//
//	sf::Clock m_staminaRecoverClock{};
//	int m_stamina{ 100 };
//	float m_staminaRecoverTime{};
//};
