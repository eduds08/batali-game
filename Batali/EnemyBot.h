#pragma once

#include "Player.h"

template <typename T>
class EnemyBot : public T
{
public:
	EnemyBot();
	virtual ~EnemyBot() = default;

protected:
	// Alters attacks between one another
	std::string m_previousAttackingAnimation{};

	// Timer used to create a interval between attacks
	sf::Clock m_timeBetweenAttacksClock{};
	float m_timeBetweenAttacks{};

	//template <class K>
	//std::shared_ptr<Player<K>> m_player{};
	float m_distanceFromPlayer{};
};

template<typename T>
inline EnemyBot<T>::EnemyBot()
{
}
