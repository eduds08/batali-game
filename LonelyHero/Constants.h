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

	constexpr int playerIdleAnimationFramesAmount{ 10 };
	constexpr int playerRunningAnimationFramesAmount{ 10 };

	constexpr int playerJumpingAnimationFramesAmount{ 3 };
	constexpr int playerFallingAnimationFramesAmount{ 3 };

	constexpr int playerAttacking2AnimationFramesAmount{ 6 };

	constexpr float playerFirstPositionX{ 232.f };
	constexpr float playerFirstPositionY{ 300.f };
	
	constexpr float playerSpriteScale = 2.f;

	constexpr float playerSpeed{ 240.f };
	constexpr float playerJumpSpeed{ 130.f };

	constexpr float gravity{ 981.f };



}