#include "PlayerFactory.h"

#include "PlayerRenderComponent.h"
#include "PlayerAnimationComponent.h"
#include "PlayerCollisionComponent.h"
#include "PlayerPhysicsComponent.h"

#include "BoxerAttackComponent.h"
#include "WindHashasinAttackComponent.h"
#include "FireKnightAttackComponent.h"

#include "PlayerFallingState.h"

#include "Player.h"

std::unique_ptr<Player> PlayerFactory::createPlayer(const std::string& characterName)
{
	std::unique_ptr<Player> newPlayer = nullptr;

	if (characterName == "fire_knight")
	{
		newPlayer = createFireKnight();
	}
	else if (characterName == "wind_hashashin")
	{
		newPlayer = createWindHashashin();
	}
	else if (characterName == "boxer")
	{
		newPlayer = createBoxer();
	}

	if (newPlayer)
	{
		newPlayer->getSprite().setOrigin(newPlayer->getSpriteSize().x / 2.f, newPlayer->getSpriteSize().y / 2.f);
		newPlayer->getShape().setOrigin(newPlayer->getShape().getSize() / 2.f);

		newPlayer->getShape().setPosition(LEFT_CHARACTER_FIRST_POSITION);

		newPlayer->getShape().setOutlineColor(sf::Color::Red);
		newPlayer->getShape().setOutlineThickness(1.f);

		newPlayer->setName(characterName);
		newPlayer->setPlayerState(std::make_unique<PlayerFallingState>());
		newPlayer->initKeyBindings();
		newPlayer->getAnimationComponent()->initTextures(*newPlayer);
		newPlayer->initAnimationThread();

		return std::move(newPlayer);
	}

	return nullptr;
}

std::unique_ptr<Player> PlayerFactory::createFireKnight()
{
	std::unique_ptr<Player> fireKnightPlayer = std::make_unique<Player>(std::make_unique<PlayerRenderComponent>(), std::make_unique<PlayerCollisionComponent>(), std::make_unique<PlayerPhysicsComponent>(), std::make_unique<PlayerAnimationComponent>());
	fireKnightPlayer->setAttackComponent(std::make_unique<FireKnightAttackComponent>());

	fireKnightPlayer->setHp(FIRE_KNIGHT_HP);
	fireKnightPlayer->setSpeed(FIRE_KNIGHT_SPEED);
	fireKnightPlayer->setJumpHeight(FIRE_KNIGHT_JUMP_HEIGHT);
	fireKnightPlayer->setRollSpeed(FIRE_KNIGHT_ROLL_SPEED);

	fireKnightPlayer->setSpriteSize(sf::Vector2i{ FIRE_KNIGHT_SPRITE_WIDTH, FIRE_KNIGHT_SPRITE_HEIGHT });
	fireKnightPlayer->getShape().setSize(sf::Vector2f{ FIRE_KNIGHT_SHAPE_WIDTH, FIRE_KNIGHT_SHAPE_HEIGHT });

    return std::move(fireKnightPlayer);
}

std::unique_ptr<Player> PlayerFactory::createWindHashashin()
{
	std::unique_ptr<Player> windHashashinPlayer = std::make_unique<Player>(std::make_unique<PlayerRenderComponent>(), std::make_unique<PlayerCollisionComponent>(), std::make_unique<PlayerPhysicsComponent>(), std::make_unique<PlayerAnimationComponent>());
	windHashashinPlayer->setAttackComponent(std::make_unique<WindHashasinAttackComponent>());

	windHashashinPlayer->setHp(WIND_HASHASHIN_HP);
	windHashashinPlayer->setSpeed(WIND_HASHASHIN_SPEED);
	windHashashinPlayer->setJumpHeight(WIND_HASHASHIN_JUMP_HEIGHT);
	windHashashinPlayer->setRollSpeed(WIND_HASHASHIN_ROLL_SPEED);

	windHashashinPlayer->setSpriteSize(sf::Vector2i{ WIND_HASHASHIN_SPRITE_WIDTH, WIND_HASHASHIN_SPRITE_HEIGHT });
	windHashashinPlayer->getShape().setSize(sf::Vector2f{ WIND_HASHASHIN_SHAPE_WIDTH, WIND_HASHASHIN_SHAPE_HEIGHT });

	return std::move(windHashashinPlayer);
}

std::unique_ptr<Player> PlayerFactory::createBoxer()
{
	std::unique_ptr<Player> boxerPlayer = std::make_unique<Player>(std::make_unique<PlayerRenderComponent>(), std::make_unique<PlayerCollisionComponent>(), std::make_unique<PlayerPhysicsComponent>(), std::make_unique<PlayerAnimationComponent>());
	boxerPlayer->setAttackComponent(std::make_unique<BoxerAttackComponent>());

	boxerPlayer->setHp(BOXER_HP);
	boxerPlayer->setSpeed(BOXER_SPEED);
	boxerPlayer->setJumpHeight(BOXER_JUMP_HEIGHT);
	boxerPlayer->setRollSpeed(BOXER_ROLL_SPEED);

	boxerPlayer->setSpriteSize(sf::Vector2i{ BOXER_SPRITE_WIDTH, BOXER_SPRITE_HEIGHT });
	boxerPlayer->getShape().setSize(sf::Vector2f{ BOXER_SHAPE_WIDTH, BOXER_SHAPE_HEIGHT });

	return std::move(boxerPlayer);
}
