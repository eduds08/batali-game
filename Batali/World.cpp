#include "World.h"

#include "PlayerRenderComponent.h"
#include "PlayerAnimationComponent.h"
#include "PlayerCollisionComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerLaunchProjectilesComponent.h"

#include "BoxerState.h"
#include "FireKnightState.h"
#include "WindHashashinState.h"

#include "PlayerFactory.h"

#include <memory>

World::~World()
{
	m_players.clear();
}

void World::init(const std::string& path, const std::string& firstCharacter, const std::string& secondCharacter)
{
	PlayerFactory playerFactory{};

	m_players.emplace_back(playerFactory.createPlayer(firstCharacter));
	m_players.emplace_back(playerFactory.createPlayer(secondCharacter));

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
