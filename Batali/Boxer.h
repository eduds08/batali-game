#pragma once

#include "Character.h"
#include "Projectile.h"
#include <memory>

class Boxer : public Character
{
public:
	Boxer(sf::Vector2f firstPosition, int playerNumber = 1, bool isBot = false, std::shared_ptr<Character> player = nullptr);
	virtual ~Boxer() = default;

	virtual void updateHitbox();

	void launchUltimate();

	std::vector<std::shared_ptr<Projectile>> m_ultimateProjectiles{};

private:
	
};
