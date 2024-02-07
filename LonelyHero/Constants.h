#pragma once

#include "SFML/Graphics.hpp"

namespace constants
{
	constexpr int tileSizeI{ 16 };
	constexpr float tileSizeF{ 16.f };
	constexpr int tilesAmountPerRow{ 50 };

	constexpr float gravity{ 981.f };

	constexpr int fireKnightSpriteWidth{ 288 };
	constexpr int fireKnightSpriteHeight{ 127 };

	constexpr float fireKnightShapeWidth{ 20.f };
	constexpr float fireKnightShapeHeight{ 40.f };

	const sf::Vector2f playerFirstPosition{sf::Vector2f{480.f, 240.f}};
	const sf::Vector2f enemyFirstPosition{sf::Vector2f{432.f, 240.f}};

	constexpr float playerSpeed{ 240.f };
	constexpr float playerJumpHeight{ 80.f };

	constexpr int playerHp{ 1250 };

	constexpr float minEnemySpeed{ 130.f };
	constexpr float maxEnemySpeed{ 200.f };
	constexpr float minEnemyDistanceFromPlayer{ 30.f };
	constexpr float maxEnemyDistanceFromPlayer{ 40.f };

	constexpr float enemyJumpHeight{ 80.f };

	constexpr int enemyHp{ 1000 };
	constexpr int enemyHpDivided5{ 200 };

	constexpr float knockbackSpeed{ 300.f };

	constexpr float fireKnightSwordHitboxWidthAttack1{ 65.f };
	constexpr float fireKnightSwordHitboxWidthAttack2{ 130.f };
	constexpr float fireKnightSwordHitboxWidthAirAttacking{ 90.f };
	constexpr float fireKnightSwordHitboxHeight{ 20.f };

	constexpr float windHashashinSwordHitboxWidthAttack1{ 30.f };
	constexpr float windHashashinSwordHitboxWidthAttack2{ 50.f };
	constexpr float windHashashinSwordHitboxHeight{ 20.f };

	constexpr float timeBetweenEnemyAttacks{ 1.f };
	constexpr float cooldownDamageTime{ 0.6f };

	constexpr int windHashashinSpriteWidth{ 288 };
	constexpr int windHashashinSpriteHeight{ 127 };

	constexpr float windHashashinShapeWidth{ 20.f };
	constexpr float windHashashinShapeHeight{ 40.f };

	constexpr int healthBarSpriteWidth{ 48 };
	constexpr int healthBarSpriteHeight{ 16 };
	constexpr int healthBarFramesAmount{ 6 };

	constexpr int buttonSpriteWidth{ 46 };
	constexpr int buttonSpriteHeight{ 14 };
}
