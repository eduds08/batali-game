#pragma once

#include "Character.h"
#include "Projectile.h"

class Boxer : public Character
{
public:
	Boxer(sf::Vector2f firstPosition, int playerNumber = 1, bool isBot = false, std::shared_ptr<Character> player = nullptr);
	virtual ~Boxer();

	virtual void updateHitbox();

	void launchUltimate();

	Projectile* m_ultimateProjectile{ nullptr };

private:
	
};
