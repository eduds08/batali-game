#pragma once

#include "SFML/Graphics.hpp"

namespace constants
{
	constexpr int screenWidth{ 640 };
	constexpr int screenHeight{ 640 };

	constexpr float viewWidth{ 300.f };
	constexpr float viewHeight{ 300.f };

	constexpr int tileSizeI{ 16 };
	constexpr float tileSizeF{ 16.f };
	constexpr int tilesAmountPerRow{ 50 };

	constexpr float gravity{ 981.f };

	constexpr int fireKnightSpriteWidth{ 288 };
	constexpr int fireKnightSpriteHeight{ 128 };

	constexpr float fireKnightShapeWidth{ 20.f };
	constexpr float fireKnightShapeHeight{ 40.f };

	constexpr int fireKnightIdleAnimationFramesAmount{ 8 };
	constexpr int fireKnightRunningAnimationFramesAmount{ 8 };

	constexpr int fireKnightJumpingAnimationFramesAmount{ 3 };
	constexpr int fireKnightFallingAnimationFramesAmount{ 3 };

	constexpr int fireKnightAttackingAnimationFramesAmount{ 11 };
	constexpr int fireKnightAttacking2AnimationFramesAmount{ 10 };

	constexpr int fireKnightDeathAnimationFramesAmount{ 13 };
	constexpr int fireKnightHitAnimationFramesAmount{ 6 };

	constexpr float fireKnightSpriteScale{ 1.f };

	const sf::Vector2f playerFirstPosition{sf::Vector2f{480.f, 240.f}};
	const sf::Vector2f enemyFirstPosition{sf::Vector2f{432.f, 240.f}};

	constexpr float playerSpeed{ 240.f };
	constexpr float playerJumpHeight{ 80.f };
	constexpr int playerHp{ 200 };
	
	constexpr float minEnemySpeed{ 130.f };
	constexpr float maxEnemySpeed{ 200.f };
	constexpr float minEnemyDistanceFromPlayer{ 30.f };
	constexpr float maxEnemyDistanceFromPlayer{ 40.f };

	constexpr float enemyJumpHeight{ 80.f };
	constexpr int enemyHp{ 200 };

	constexpr float knockbackSpeed{ 300.f };

	constexpr float fireKnightSwordHitboxWidth{ 65.f };
	constexpr float fireKnightSwordHitboxHeight{ 20.f };

	constexpr float windHashashinSwordHitboxWidthAttack1{ 30.f };
	constexpr float windHashashinSwordHitboxWidthAttack2{ 50.f };

	constexpr float windHashashinSwordHitboxHeight{ 20.f };

	constexpr float timeBetweenEnemyAttacks{ 0.8f };
	constexpr float cooldownDamageTime{ 0.6f };

	constexpr int windHashashinSpriteWidth{ 288 };
	constexpr int windHashashinSpriteHeight{ 128 };

	constexpr float windHashashinShapeWidth{ 20.f };
	constexpr float windHashashinShapeHeight{ 40.f };

	constexpr int windHashashinIdleAnimationFramesAmount{ 8 };
	constexpr int windHashashinRunningAnimationFramesAmount{ 8 };

	constexpr int windHashashinJumpingAnimationFramesAmount{ 3 };
	constexpr int windHashashinFallingAnimationFramesAmount{ 3 };

	constexpr int windHashashinAttackingAnimationFramesAmount{ 8 };
	constexpr int windHashashinAttacking2AnimationFramesAmount{ 12 };

	constexpr int windHashashinDeathAnimationFramesAmount{ 19 };
	constexpr int windHashashinHitAnimationFramesAmount{ 6 };

	constexpr float windHashashinSpriteScale{ 1.f };
}
