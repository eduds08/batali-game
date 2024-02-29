#pragma once

#include "SFML/Graphics.hpp"

namespace constants
{
	constexpr int TILE_SIZE_INT{ 16 };
	constexpr float TILE_SIZE_FLOAT{ 16.f };
	constexpr int TILES_AMOUNT_PER_ROW{ 60 };
	constexpr int TILES_AMOUNT_PER_COL{ 34 };

	constexpr float GRAVITY{ 981.f };

	constexpr float KNOCKBACK_SPEED{ 300.f };

	constexpr int BUTTON_WIDTH{ 46 };
	constexpr int BUTTON_HEIGHT{ 14 };

	constexpr int CHARACTER_PORTRAIT_WIDTH{ 64 };
	constexpr int CHARACTER_PORTRAIT_HEIGHT{ 64 };

	const sf::Vector2f LEFT_CHARACTER_FIRST_POSITION{ sf::Vector2f{(TILES_AMOUNT_PER_ROW / 2.f) * TILE_SIZE_FLOAT - 50.f, (TILES_AMOUNT_PER_COL / 2.f) * TILE_SIZE_FLOAT} };
	const sf::Vector2f RIGHT_CHARACTER_FIRST_POSITION{ sf::Vector2f{(TILES_AMOUNT_PER_ROW / 2.f) * TILE_SIZE_FLOAT + 50.f, (TILES_AMOUNT_PER_COL / 2.f) * TILE_SIZE_FLOAT} };

	constexpr int CHARACTER_LOGO_STATUS_WIDTH{ 78 };
	constexpr int CHARACTER_LOGO_STATUS_HEIGHT{ 72 };

	constexpr int HEALTH_BAR_WIDTH{ 153 };
	constexpr int HEALTH_BAR_HEIGHT{ 18 };

	constexpr int STAMINA_BAR_WIDTH{ 141 };
	constexpr int STAMINA_BAR_HEIGHT{ 18 };

	constexpr int MANA_BAR_WIDTH{ 120 };
	constexpr int MANA_BAR_HEIGHT{ 36 };

	/* FIRE KNIGHT CONSTANTS: */

	constexpr int FIRE_KNIGHT_SPRITE_WIDTH{ 288 };
	constexpr int FIRE_KNIGHT_SPRITE_HEIGHT{ 127 };

	constexpr float FIRE_KNIGHT_SHAPE_WIDTH{ 20.f };
	constexpr float FIRE_KNIGHT_SHAPE_HEIGHT{ 40.f };

	constexpr float FIRE_KNIGHT_SPEED{ 230.f };
	constexpr float FIRE_KNIGHT_JUMP_HEIGHT{ 80.f };
	 
	constexpr int FIRE_KNIGHT_HP{ 1250 };

	constexpr float FIRE_KNIGHT_ATTACK_1_WIDTH{ 65.f };
	constexpr float FIRE_KNIGHT_ATTACK_2_WIDTH{ 130.f };
	constexpr float FIRE_KNIGHT_AIR_ATTACK_WIDTH{ 90.f };
	constexpr float FIRE_KNIGHT_ATTACK_HEIGHT{ 20.f };

	constexpr int FIRE_KNIGHT_ATTACK_1_DAMAGE{100};
	constexpr int FIRE_KNIGHT_ATTACK_2_DAMAGE{80};
	constexpr int FIRE_KNIGHT_AIR_ATTACK_DAMAGE{70};

	/* WIND HASHASHIN CONSTANTS: */

	constexpr int WIND_HASHASHIN_SPRITE_WIDTH{ 288 };
	constexpr int WIND_HASHASHIN_SPRITE_HEIGHT{ 127 };

	constexpr float WIND_HASHASHIN_SHAPE_WIDTH{ 20.f };
	constexpr float WIND_HASHASHIN_SHAPE_HEIGHT{ 40.f };

	constexpr float WIND_HASHASHIN_SPEED{ 240.f };
	constexpr float WIND_HASHASHIN_JUMP_HEIGHT{ 80.f };

	constexpr int WIND_HASHASHIN_HP{ 1000 };

	constexpr float WIND_HASHASHIN_ATTACK_1_WIDTH{ 30.f };
	constexpr float WIND_HASHASHIN_ATTACK_2_WIDTH{ 50.f };
	constexpr float WIND_HASHASHIN_AIR_ATTACK_WIDTH{ 53.f };
	constexpr float WIND_HASHASHIN_ATTACK_HEIGHT{ 20.f };

	constexpr int WIND_HASHASHIN_ATTACK_1_DAMAGE{80};
	constexpr int WIND_HASHASHIN_ATTACK_2_DAMAGE{75};
	constexpr int WIND_HASHASHIN_AIR_ATTACK_DAMAGE{65};

	/* BOT CONSTANTS: */

	constexpr float MIN_ENEMY_SPEED{ 200.f };
	constexpr float MAX_ENEMY_SPEED{ 230.f };
	constexpr float MIN_ENEMY_DISTANCE_FROM_PLAYER{ 30.f };
	constexpr float MAX_ENEMY_DISTANCE_FROM_PLAYER{ 40.f };

	constexpr float TIME_BETWEEN_ENEMY_ATTACKS{ 1.f };
	constexpr float COOLDOWN_IMMUNE_TIME{ 0.6f };

	/* STATE CONSTANTS: */

	const std::string MENU_TO_SINGLEPLAYER{"transitionToSingleplayerCharacterSelection"};
	const std::string MENU_TO_MULTIPLAYER{"transitionToMultiplayerCharacterSelection"};
	const std::string EXIT_GAME{"exiting"};

	const std::string MAIN_MENU_STATE{"main"};
	const std::string PLAYING_STATE{"playing"};

	const std::string EXIT_PLAYING{"quittingPlaying"};

	const std::string CHARACTER_SELECTION_STATE{"characterSelection"};

	const std::string CHARACTER_SELECTION_TO_SINGLEPLAYER{ "transitionToSingleplayer" };
	const std::string CHARACTER_SELECTION_TO_MULTIPLAYER{ "transitionToMultiplayer" };

	const std::string CHARACTER_SELECTION_RESET{ "characterSelectionReset" };
}
