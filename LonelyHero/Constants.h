#pragma once

#include "SFML/Graphics.hpp"

namespace constants
{
	constexpr int screenWidth{ 600 };
	constexpr int screenHeight{ 600 };

	constexpr int playerSpriteWidth{ 120 };
	constexpr int playerSpriteHeight{ 80 };

	constexpr float playerShapeWidth{ 30.f };
	constexpr float playerShapeHeight{ 80.f };

	constexpr int playerIdleAnimationFramesAmount{ 10 };
	constexpr float playerSwitchAnimationTime{ 0.1f };

	constexpr float playerFirstPositionX{ 300.f };
	constexpr float playerFirstPositionY{ 0.f };
	
	constexpr float playerSpriteScale = 2.f;

	constexpr float playerSpeed{ 240.f };
	constexpr float playerJumpSpeed{ 100.f };

	constexpr float gravity{ 981.f };



}