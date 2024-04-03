#include "World.h"

#include "Player.h"

World::~World()
{
	for (std::vector<Player*>::iterator it = m_players.begin(); it != m_players.end(); ++it)
	{
		delete *it;
		*it = nullptr;
	}

	m_players.clear();
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
