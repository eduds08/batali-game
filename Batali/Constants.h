#pragma once

#include "SFML/Graphics.hpp"

namespace constants
{
	constexpr int TILE_SIZE_INT{ 32 };
	constexpr float TILE_SIZE_FLOAT{ 32.f };
	constexpr int TILES_AMOUNT_PER_ROW{ 60 };
	constexpr int TILES_AMOUNT_PER_COL{ 34 };
	constexpr int TILES_PHYSICAL_ENTITY_LIMIT { 5 };

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

	const sf::Color PLAYER_1_COLOR{179, 245, 188};
	const sf::Color PLAYER_2_COLOR{250, 145, 137};

	constexpr int TOTAL_STAMINA{ 100 };

	const sf::Vector2f BUTTON_TEXT_ON_HOVER_OFFSET{ 0.f, 2.f };

	/* FIRE KNIGHT CONSTANTS: */

	constexpr int FIRE_KNIGHT_SPRITE_WIDTH{ 288 };
	constexpr int FIRE_KNIGHT_SPRITE_HEIGHT{ 127 };

	constexpr float FIRE_KNIGHT_SHAPE_WIDTH{ 20.f };
	constexpr float FIRE_KNIGHT_SHAPE_HEIGHT{ 40.f };

	constexpr float FIRE_KNIGHT_SPEED{ 220.f };
	constexpr float FIRE_KNIGHT_JUMP_HEIGHT{ 85.f };
	 
	constexpr float FIRE_KNIGHT_ROLL_SPEED{ 220.f };

	constexpr int FIRE_KNIGHT_HP{ 1250 };

	constexpr float FIRE_KNIGHT_ATTACK_1_WIDTH{ 65.f };
	constexpr float FIRE_KNIGHT_ATTACK_1_HEIGHT{ 20.f };

	constexpr float FIRE_KNIGHT_ATTACK_2_PT_1_WIDTH{ 50.f };
	constexpr float FIRE_KNIGHT_ATTACK_2_PT_1_HEIGHT{ 20.f };

	constexpr float FIRE_KNIGHT_ATTACK_2_PT_2_WIDTH{ 70.f };
	constexpr float FIRE_KNIGHT_ATTACK_2_PT_2_HEIGHT{ 20.f };

	constexpr float FIRE_KNIGHT_ATTACK_2_PT_3_WIDTH{ 60.f };
	constexpr float FIRE_KNIGHT_ATTACK_2_PT_3_HEIGHT{ 20.f };

	constexpr float FIRE_KNIGHT_ATTACK_2_PT_4_WIDTH{ 70.f };
	constexpr float FIRE_KNIGHT_ATTACK_2_PT_4_HEIGHT{ 20.f };

	constexpr float FIRE_KNIGHT_AIR_ATTACK_WIDTH{ 95.f };
	constexpr float FIRE_KNIGHT_AIR_ATTACK_HEIGHT{ 20.f };

	constexpr float FIRE_KNIGHT_ULTIMATE_WIDTH{ 100.f };
	constexpr float FIRE_KNIGHT_ULTIMATE_HEIGHT{ 20.f };

	constexpr int FIRE_KNIGHT_ATTACK_1_DAMAGE{ 95 };
	constexpr int FIRE_KNIGHT_ATTACK_2_DAMAGE{ 80 };
	constexpr int FIRE_KNIGHT_AIR_ATTACK_DAMAGE{ 75 };
	constexpr int FIRE_KNIGHT_ULTIMATE_DAMAGE{ 115 };

	/* WIND HASHASHIN CONSTANTS: */

	constexpr int WIND_HASHASHIN_SPRITE_WIDTH{ 288 };
	constexpr int WIND_HASHASHIN_SPRITE_HEIGHT{ 127 };

	constexpr float WIND_HASHASHIN_SHAPE_WIDTH{ 20.f };
	constexpr float WIND_HASHASHIN_SHAPE_HEIGHT{ 35.f };

	constexpr float WIND_HASHASHIN_SPEED{ 260.f };
	constexpr float WIND_HASHASHIN_JUMP_HEIGHT{ 100.f };

	constexpr float WIND_HASHASHIN_ROLL_SPEED{ 260.f };

	constexpr int WIND_HASHASHIN_HP{ 1000 };

	constexpr float WIND_HASHASHIN_ATTACK_1_PT_1_WIDTH{ 38.f };
	constexpr float WIND_HASHASHIN_ATTACK_1_PT_1_HEIGHT{ 20.f };

	constexpr float WIND_HASHASHIN_ATTACK_1_PT_2_WIDTH{ 28.f };
	constexpr float WIND_HASHASHIN_ATTACK_1_PT_2_HEIGHT{ 20.f };

	constexpr float WIND_HASHASHIN_ATTACK_2_WIDTH{ 50.f };
	constexpr float WIND_HASHASHIN_ATTACK_2_HEIGHT{ 20.f };

	constexpr float WIND_HASHASHIN_AIR_ATTACK_WIDTH{ 53.f };
	constexpr float WIND_HASHASHIN_AIR_ATTACK_HEIGHT{ 20.f };

	constexpr float WIND_HASHASHIN_ACTIVATE_ULTIMATE_WIDTH{ 80.f };
	constexpr float WIND_HASHASHIN_ACTIVATE_ULTIMATE_HEIGHT{ 20.f };

	constexpr int WIND_HASHASHIN_ATTACK_1_DAMAGE{ 100 };
	constexpr int WIND_HASHASHIN_ATTACK_2_DAMAGE{ 85 };
	constexpr int WIND_HASHASHIN_AIR_ATTACK_DAMAGE{ 90 };
	constexpr int WIND_HASHASHIN_ULTIMATE_DAMAGE{ 60 };

	/* BOXER CONSTANTS: */

	constexpr int BOXER_SPRITE_WIDTH{ 288 };
	constexpr int BOXER_SPRITE_HEIGHT{ 127 };

	constexpr float BOXER_SHAPE_WIDTH{ 20.f };
	constexpr float BOXER_SHAPE_HEIGHT{ 35.f };

	constexpr float BOXER_SPEED{ 260.f };
	constexpr float BOXER_JUMP_HEIGHT{ 100.f };

	constexpr float BOXER_ROLL_SPEED{ 160.f };

	constexpr int BOXER_HP{ 1000 };

	constexpr float BOXER_ATTACK_1_WIDTH{ 33.f };
	constexpr float BOXER_ATTACK_1_HEIGHT{ 15.f };

	constexpr float BOXER_ATTACK_2_WIDTH{ 8.f };
	constexpr float BOXER_ATTACK_2_HEIGHT{ 10.f };

	constexpr float BOXER_AIR_ATTACK_WIDTH{ 30.f };
	constexpr float BOXER_AIR_ATTACK_HEIGHT{ 25.f };

	constexpr int BOXER_ULTIMATE_PROJECTILE_SPRITE_WIDTH{ 30 };
	constexpr int BOXER_ULTIMATE_PROJECTILE_SPRITE_HEIGHT{ 30 };

	constexpr float BOXER_ULTIMATE_PROJECTILE_SHAPE_WIDTH{ 10.f };
	constexpr float BOXER_ULTIMATE_PROJECTILE_SHAPE_HEIGHT{ 10.f };

	constexpr int BOXER_ATTACK_1_DAMAGE{ 100 };
	constexpr int BOXER_ATTACK_2_DAMAGE{ 85 };
	constexpr int BOXER_AIR_ATTACK_DAMAGE{ 90 };
	constexpr int BOXER_ULTIMATE_DAMAGE{ 45 };

	const sf::Vector2f BOXER_PROJECTILE_OFFSET_POSITION{ 0.f, -7.f };

	/* HOODIE CONSTANTS: */

	constexpr int HOODIE_SPRITE_WIDTH{ 288 };
	constexpr int HOODIE_SPRITE_HEIGHT{ 127 };

	constexpr float HOODIE_SHAPE_WIDTH{ 20.f };
	constexpr float HOODIE_SHAPE_HEIGHT{ 40.f };

	constexpr float HOODIE_SPEED{ 220.f };
	constexpr float HOODIE_JUMP_HEIGHT{ 85.f };

	constexpr float HOODIE_ROLL_SPEED{ 220.f };

	constexpr int HOODIE_HP{ 1250 };

	constexpr float HOODIE_ATTACK_1_WIDTH{ 65.f };
	constexpr float HOODIE_ATTACK_1_HEIGHT{ 20.f };

	constexpr float HOODIE_ATTACK_2_WIDTH{ 50.f };
	constexpr float HOODIE_ATTACK_2_HEIGHT{ 20.f };

	constexpr float HOODIE_AIR_ATTACK_WIDTH{ 95.f };
	constexpr float HOODIE_AIR_ATTACK_HEIGHT{ 20.f };

	constexpr float HOODIE_ULTIMATE_WIDTH{ 100.f };
	constexpr float HOODIE_ULTIMATE_HEIGHT{ 20.f };

	constexpr int HOODIE_ATTACK_1_DAMAGE{ 95 };
	constexpr int HOODIE_ATTACK_2_DAMAGE{ 80 };
	constexpr int HOODIE_AIR_ATTACK_DAMAGE{ 75 };
	constexpr int HOODIE_ULTIMATE_DAMAGE{ 115 };

	/* ATTACK HITBOX FRAMES */

	/* FIRE_KNIGHT FRAMES */

	constexpr int FIRE_KNIGHT_ATTACK_1_STARTING_FRAME{ 5 };
	constexpr int FIRE_KNIGHT_ATTACK_1_ENDING_FRAME{ 7 };

	constexpr int FIRE_KNIGHT_ATTACK_2_PT_1_STARTING_FRAME{ 2 };
	constexpr int FIRE_KNIGHT_ATTACK_2_PT_1_ENDING_FRAME{ 2 };
	constexpr int FIRE_KNIGHT_ATTACK_2_PT_2_STARTING_FRAME{ 4 };
	constexpr int FIRE_KNIGHT_ATTACK_2_PT_2_ENDING_FRAME{ 4 };
	constexpr int FIRE_KNIGHT_ATTACK_2_PT_3_STARTING_FRAME{ 5 };
	constexpr int FIRE_KNIGHT_ATTACK_2_PT_3_ENDING_FRAME{ 5 };
	constexpr int FIRE_KNIGHT_ATTACK_2_PT_4_STARTING_FRAME{ 6 };
	constexpr int FIRE_KNIGHT_ATTACK_2_PT_4_ENDING_FRAME{ 6 };

	constexpr int FIRE_KNIGHT_AIR_ATTACK_STARTING_FRAME{ 4 };
	constexpr int FIRE_KNIGHT_AIR_ATTACK_ENDING_FRAME{ 5 };

	constexpr int FIRE_KNIGHT_ULTIMATE_STARTING_FRAME{ 5 };
	constexpr int FIRE_KNIGHT_ULTIMATE_ENDING_FRAME{ 7 };

	/* WIND_HASHASHIN FRAMES */

	constexpr int WIND_HASHASHIN_ATTACK_1_PT_1_STARTING_FRAME{ 0 };
	constexpr int WIND_HASHASHIN_ATTACK_1_PT_1_ENDING_FRAME{ 1 };
	constexpr int WIND_HASHASHIN_ATTACK_1_PT_2_STARTING_FRAME{ 3 };
	constexpr int WIND_HASHASHIN_ATTACK_1_PT_2_ENDING_FRAME{ 3 };

	constexpr int WIND_HASHASHIN_ATTACK_2_STARTING_FRAME{ 1 };
	constexpr int WIND_HASHASHIN_ATTACK_2_ENDING_FRAME{ 7 };

	constexpr int WIND_HASHASHIN_AIR_ATTACK_STARTING_FRAME{ 2 };
	constexpr int WIND_HASHASHIN_AIR_ATTACK_ENDING_FRAME{ 5 };

	constexpr int WIND_HASHASHIN_ACTIVATE_ULTIMATE_STARTING_FRAME{ 5 };
	constexpr int WIND_HASHASHIN_ACTIVATE_ULTIMATE_ENDING_FRAME{ 7 };

	constexpr int WIND_HASHASHIN_ULTIMATE_FIRST_FRAME{ 11 };
	constexpr int WIND_HASHASHIN_ULTIMATE_SECOND_FRAME{ 17 };
	constexpr int WIND_HASHASHIN_ULTIMATE_THIRD_FRAME{ 19 };

	/* BOXER FRAMES */

	constexpr int BOXER_ATTACK_1_STARTING_FRAME{ 4 };
	constexpr int BOXER_ATTACK_1_ENDING_FRAME{ 5 };

	constexpr int BOXER_ATTACK_2_STARTING_FRAME{ 7 };
	constexpr int BOXER_ATTACK_2_ENDING_FRAME{ 7 };

	constexpr int BOXER_AIR_ATTACK_STARTING_FRAME{ 1 };
	constexpr int BOXER_AIR_ATTACK_ENDING_FRAME{ 4 };

	constexpr int BOXER_ULTIMATE_PT_1_FRAME{ 9 };
	constexpr int BOXER_ULTIMATE_PT_2_FRAME{ 13 };

	/* HOODIE FRAMES */

	constexpr int HOODIE_ATTACK_1_STARTING_FRAME{ 5 };
	constexpr int HOODIE_ATTACK_1_ENDING_FRAME{ 7 };

	constexpr int HOODIE_ATTACK_2_STARTING_FRAME{ 2 };
	constexpr int HOODIE_ATTACK_2_ENDING_FRAME{ 2 };

	constexpr int HOODIE_AIR_ATTACK_STARTING_FRAME{ 4 };
	constexpr int HOODIE_AIR_ATTACK_ENDING_FRAME{ 5 };

	constexpr int HOODIE_ULTIMATE_STARTING_FRAME{ 5 };
	constexpr int HOODIE_ULTIMATE_ENDING_FRAME{ 7 };

	/* BOT CONSTANTS: */

	constexpr float ENEMY_SPEED{ 175.f };
	constexpr float ENEMY_DISTANCE_FROM_PLAYER{ 35.f };

	constexpr float TIME_BETWEEN_ENEMY_ATTACKS{ 1.f };

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
