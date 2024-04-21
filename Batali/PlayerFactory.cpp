#include "PlayerFactory.h"

#include "PlayerRenderComponent.h"
#include "PlayerAnimationComponent.h"
#include "PlayerCollisionComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerLaunchProjectilesComponent.h"

#include "BoxerState.h"
#include "FireKnightState.h"
#include "WindHashashinState.h"

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
	fireKnightPlayer->setChosenCharacter(std::make_unique<FireKnightState>());

    return std::move(fireKnightPlayer);
}

std::unique_ptr<Player> PlayerFactory::createWindHashashin()
{
	std::unique_ptr<Player> windHashashinPlayer = std::make_unique<Player>(std::make_unique<PlayerRenderComponent>(), std::make_unique<PlayerCollisionComponent>(), std::make_unique<PlayerPhysicsComponent>(), std::make_unique<PlayerAnimationComponent>());
	windHashashinPlayer->setChosenCharacter(std::make_unique<WindHashashinState>());

	return std::move(windHashashinPlayer);
}

std::unique_ptr<Player> PlayerFactory::createBoxer()
{
	std::unique_ptr<Player> boxerPlayer = std::make_unique<Player>(std::make_unique<PlayerRenderComponent>(), std::make_unique<PlayerCollisionComponent>(), std::make_unique<PlayerPhysicsComponent>(), std::make_unique<PlayerAnimationComponent>(), std::make_unique<PlayerLaunchProjectilesComponent>());
	boxerPlayer->setChosenCharacter(std::make_unique<BoxerState>());

	return std::move(boxerPlayer);
}
