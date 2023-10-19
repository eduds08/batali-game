#pragma once

#include "SFML/Graphics.hpp"

namespace constants
{
	constexpr int screenWidth{ 640 };
	constexpr int screenHeight{ 640 };

	constexpr float viewWidth{ 300.f };
	constexpr float viewHeight{ 300.f };

	constexpr float gravity{ 981.f };

	constexpr int knightSpriteWidth{ 288 };
	constexpr int knightSpriteHeight{ 128 };

	constexpr float knightShapeWidth{ 15.f };
	constexpr float knightShapeHeight{ 30.f };

	constexpr int knightIdleAnimationFramesAmount{ 8 };
	constexpr int knightRunningAnimationFramesAmount{ 8 };

	constexpr int knightJumpingAnimationFramesAmount{ 3 };
	constexpr int knightFallingAnimationFramesAmount{ 3 };

	constexpr int knightAttackingAnimationFramesAmount{ 11 };
	constexpr int knightAttacking2AnimationFramesAmount{ 10 };

	constexpr int knightDeathAnimationFramesAmount{ 13 };
	constexpr int knightHitAnimationFramesAmount{ 6 };

	constexpr float knightSpriteScale{ 1.f };

	const sf::Vector2f playerFirstPosition{sf::Vector2f{480.f, 240.f}};
	const sf::Vector2f enemyFirstPosition{sf::Vector2f{432.f, 240.f}};

	constexpr float playerSpeed{ 240.f };
	constexpr float playerJumpSpeed{ 80.f };

	constexpr float enemySpeed{ 150.f };

	constexpr float knockbackSpeed{ 300.f };

	constexpr float swordHitboxWidth{ 35.f };
	constexpr float swordHitboxHeight{ 15.f };

	constexpr float timeBetweenEnemyAttacks{ 0.8f };
	constexpr float cooldownDamageTime{ 0.4f };

	constexpr int tileSizeI{ 16 };
	constexpr float tileSizeF{ 16.f };
	constexpr int tilesAmountPerRow{ 50 };

	constexpr float enemyDistanceFromPlayer{ 30.f };

	constexpr int martialSpriteWidth{ 200 };
	constexpr int martialSpriteHeight{ 200 };

	constexpr float martialShapeWidth{ 30.f };
	constexpr float martialShapeHeight{ 50.f };

	constexpr int martialIdleAnimationFramesAmount{ 8 };
	constexpr int martialRunningAnimationFramesAmount{ 8 };

	constexpr int martialJumpingAnimationFramesAmount{ 2 };
	constexpr int martialFallingAnimationFramesAmount{ 2 };

	constexpr int martialAttackingAnimationFramesAmount{ 6 };
	constexpr int martialAttacking2AnimationFramesAmount{ 6 };

	constexpr int martialDeathAnimationFramesAmount{ 6 };
	constexpr int martialHitAnimationFramesAmount{ 4 };

	constexpr float martialSpriteScale{ 1.f };
}
