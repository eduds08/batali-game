#pragma once

#include "SFML/Graphics.hpp"

namespace constants
{
	constexpr int screenWidth{ 640 };
	constexpr int screenHeight{ 640 };

	constexpr int playerSpriteWidth{ 120 };
	constexpr int playerSpriteHeight{ 80 };

	constexpr float playerShapeWidth{ 30.f };
	constexpr float playerShapeHeight{ 70.f };

	constexpr int enemySpriteWidth{ 120 };
	constexpr int enemySpriteHeight{ 80 };

	constexpr float enemyShapeWidth{ 30.f };
	constexpr float enemyShapeHeight{ 70.f };

	constexpr int enemyIdleAnimationFramesAmount{ 10 };
	constexpr int enemyRunningAnimationFramesAmount{ 10 };

	constexpr int playerIdleAnimationFramesAmount{ 10 };
	constexpr int playerRunningAnimationFramesAmount{ 10 };

	constexpr int playerJumpingAnimationFramesAmount{ 3 };
	constexpr int playerFallingAnimationFramesAmount{ 3 };

	constexpr int playerAttackingAnimationFramesAmount{ 4 };
	constexpr int playerAttacking2AnimationFramesAmount{ 6 };

	const sf::Vector2f playerFirstPosition{sf::Vector2f{232.f, 300.f}};

	constexpr float playerSpriteScale = 2.f;

	const sf::Vector2f enemyFirstPosition{sf::Vector2f{432.f, 300.f}};

	constexpr float enemySpriteScale = 2.f;

	constexpr float playerSpeed{ 240.f };
	constexpr float playerJumpSpeed{ 130.f };

	constexpr float enemySpeed{ 150.f };

	constexpr float gravity{ 981.f };

	constexpr float swordHitboxWidth{ 70.f };
	constexpr float swordHitboxHeight{ 30.f };



}