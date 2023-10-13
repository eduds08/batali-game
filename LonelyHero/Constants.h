#pragma once

#include "SFML/Graphics.hpp"

namespace constants
{
	constexpr int screenWidth{ 640 };
	constexpr int screenHeight{ 640 };

	constexpr float gravity{ 981.f };

	constexpr int knightSpriteWidth{ 120 };
	constexpr int knightSpriteHeight{ 80 };

	constexpr float knightShapeWidth{ 30.f };
	constexpr float knightShapeHeight{ 70.f };

	constexpr int knightIdleAnimationFramesAmount{ 10 };
	constexpr int knightRunningAnimationFramesAmount{ 10 };

	constexpr int knightJumpingAnimationFramesAmount{ 3 };
	constexpr int knightFallingAnimationFramesAmount{ 3 };

	constexpr int knightAttackingAnimationFramesAmount{ 4 };
	constexpr int knightAttacking2AnimationFramesAmount{ 6 };

	constexpr int knightHitAnimationFramesAmount{ 5 };

	constexpr float knightSpriteScale = 2.f;

	const sf::Vector2f playerFirstPosition{sf::Vector2f{232.f, 300.f}};
	const sf::Vector2f enemyFirstPosition{sf::Vector2f{432.f, 300.f}};

	constexpr float playerSpeed{ 240.f };
	constexpr float playerJumpSpeed{ 130.f };

	constexpr float enemySpeed{ 150.f };

	constexpr float swordHitboxWidth{ 70.f };
	constexpr float swordHitboxHeight{ 30.f };
}
