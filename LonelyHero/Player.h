#pragma once

#include "AnimatedEntity.h"
#include "ColliderEntity.h"
#include "Constants.h"

class Player : public AnimatedEntity, public ColliderEntity
{
public:
	Player(int spriteWidth, int spriteHeight, int animationFramesAmount, float shapeWidth, float shapeHeight, float spriteScale, sf::Vector2f firstPosition, const std::string& textureName, const std::string& texturePath);
	virtual ~Player() = default;

	void update(float& deltaTime);

	void updateMovement(float& deltaTime);
	

	void updateAttack();

	

	void checkIfCanJump();

	virtual void updateTexture();

private:
	bool m_canJump{ false };
	/*int m_facingRight{ 1 };*/

	/*bool m_isAttacking{ false };*/

	/*std::string m_previousAttackingAnimation{};*/
};
