#include "World.h"

#include "PlayerRenderComponent.h"
#include "PlayerAnimationComponent.h"
#include "PlayerCollisionComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerLaunchProjectilesComponent.h"

#include "BoxerState.h"
#include "FireKnightState.h"
#include "WindHashashinState.h"

#include <memory>

World::~World()
{
	m_players.clear();
}

void World::init(const std::string& path, const std::string& firstCharacter, const std::string& secondCharacter)
{
	// Initialize Player 1
	if (firstCharacter == "fire_knight")
	{
		m_players.emplace_back(std::make_unique<Player>(std::make_unique<PlayerRenderComponent>(), std::make_unique<PlayerCollisionComponent>(), std::make_unique<PlayerPhysicsComponent>(), nullptr, std::make_unique<PlayerAnimationComponent>()));
		m_players[0]->initChosenCharacter(std::make_unique<FireKnightState>());
	}
	else if (firstCharacter == "wind_hashashin")
	{
		m_players.emplace_back(std::make_unique<Player>(std::make_unique<PlayerRenderComponent>(), std::make_unique<PlayerCollisionComponent>(), std::make_unique<PlayerPhysicsComponent>(), nullptr, std::make_unique<PlayerAnimationComponent>()));
		m_players[0]->initChosenCharacter(std::make_unique<WindHashashinState>());
	}
	else if (firstCharacter == "boxer")
	{
		m_players.emplace_back(std::make_unique<Player>(std::make_unique<PlayerRenderComponent>(), std::make_unique<PlayerCollisionComponent>(), std::make_unique<PlayerPhysicsComponent>(), std::make_unique<PlayerLaunchProjectilesComponent>(), std::make_unique<PlayerAnimationComponent>()));
		m_players[0]->initChosenCharacter(std::make_unique<BoxerState>());
	}

	// Initialize Player 2
	if (secondCharacter == "fire_knight")
	{
		m_players.emplace_back(std::make_unique<Player>(std::make_unique<PlayerRenderComponent>(), std::make_unique<PlayerCollisionComponent>(), std::make_unique<PlayerPhysicsComponent>(), nullptr, std::make_unique<PlayerAnimationComponent>()));
		m_players[1]->initChosenCharacter(std::make_unique<FireKnightState>());
	}
	else if (secondCharacter == "wind_hashashin")
	{
		m_players.emplace_back(std::make_unique<Player>(std::make_unique<PlayerRenderComponent>(), std::make_unique<PlayerCollisionComponent>(), std::make_unique<PlayerPhysicsComponent>(), nullptr, std::make_unique<PlayerAnimationComponent>()));
		m_players[1]->initChosenCharacter(std::make_unique<WindHashashinState>());
	}
	else if (secondCharacter == "boxer")
	{
		m_players.emplace_back(std::make_unique<Player>(std::make_unique<PlayerRenderComponent>(), std::make_unique<PlayerCollisionComponent>(), std::make_unique<PlayerPhysicsComponent>(), std::make_unique<PlayerLaunchProjectilesComponent>(), std::make_unique<PlayerAnimationComponent>()));
		m_players[1]->initChosenCharacter(std::make_unique<BoxerState>());
	}

	loadTiles(path);
}

void World::loadTiles(const std::string& path)
{
	std::fstream mapFile{ path, std::ios::in };
	std::string row{};

	int x{ 0 };
	int y{ 0 };

	std::string tileId{};

	while (std::getline(mapFile, row))
	{
		for (int i = 0; i < TILES_AMOUNT_PER_ROW; i++)
		{
			mapFile >> tileId;
			if (tileId != "0")
			{
				m_tiles.emplace_back(Ground{ sf::Vector2f{x * TILE_SIZE_FLOAT + TILE_SIZE_FLOAT / 2.f, y * TILE_SIZE_FLOAT + TILE_SIZE_FLOAT / 2.f}, tileId,  "./tiles/" + tileId + ".png" });
			}
			++x;
		}
		x = 0;
		++y;
	}

	mapFile.close();
}
