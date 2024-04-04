#pragma once

#include <vector>
#include <fstream>
#include "Ground.h"

#include "Player.h"

class World
{
public:
	World() {}
	virtual ~World();

	void loadTiles(const std::string& path);

	std::vector<Ground> m_tiles{};

	std::vector<std::unique_ptr<Player>> m_players{};
};
