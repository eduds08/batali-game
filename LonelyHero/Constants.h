#pragma once

#include "SFML/Graphics.hpp"

namespace constants
{
	constexpr int tileSizeI{ 16 };
	constexpr float tileSizeF{ 16.f };
	constexpr int tilesAmountPerRow{ 50 };

	constexpr float gravity{ 981.f };

	constexpr float knockbackSpeed{ 300.f };

	constexpr int healthBarSpriteWidth{ 48 };
	constexpr int healthBarSpriteHeight{ 16 };

	constexpr int buttonSpriteWidth{ 46 };
	constexpr int buttonSpriteHeight{ 14 };

	/* FIRE KNIGHT CONSTANTS: */

	constexpr int fireKnightSpriteWidth{ 288 };
	constexpr int fireKnightSpriteHeight{ 127 };

	constexpr float fireKnightShapeWidth{ 20.f };
	constexpr float fireKnightShapeHeight{ 40.f };

	const sf::Vector2f fireKnightFirstPosition{sf::Vector2f{480.f, 240.f}};

	constexpr float fireKnightSpeed{ 240.f };
	constexpr float fireKnightJumpHeight{ 80.f };
	 
	constexpr int fireKnightHp{ 1250 };

	constexpr float fireKnightSwordHitboxWidthAttack1{ 65.f };
	constexpr float fireKnightSwordHitboxWidthAttack2{ 130.f };
	constexpr float fireKnightSwordHitboxWidthAirAttacking{ 90.f };
	constexpr float fireKnightSwordHitboxHeight{ 20.f };

	/* WIND HASHASHIN CONSTANTS: */

	constexpr int windHashashinSpriteWidth{ 288 };
	constexpr int windHashashinSpriteHeight{ 127 };

	constexpr float windHashashinShapeWidth{ 20.f };
	constexpr float windHashashinShapeHeight{ 40.f };

	const sf::Vector2f windHashashinFirstPosition{sf::Vector2f{432.f, 240.f}};

	constexpr float windHashashinSpeed{ 260.f };
	constexpr float windHashashinJumpHeight{ 80.f };

	constexpr int windHashashinHp{ 1000 };

	constexpr float windHashashinSwordHitboxWidthAttack1{ 30.f };
	constexpr float windHashashinSwordHitboxWidthAttack2{ 50.f };
	constexpr float windHashashinSwordHitboxWidthAirAttacking{ 53.f };
	constexpr float windHashashinSwordHitboxHeight{ 20.f };

	constexpr int windHashashinHpDivided5{ 200 };

	/* BOT CONSTANTS: */

	constexpr float minBotSpeed{ 130.f };
	constexpr float maxBotSpeed{ 200.f };
	constexpr float minBotDistanceFromPlayer{ 30.f };
	constexpr float maxBotDistanceFromPlayer{ 40.f };

	constexpr float timeBetweenBotAttacks{ 1.f };
	constexpr float cooldownDamageTime{ 0.6f };
}
