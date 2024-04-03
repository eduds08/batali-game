#pragma once

#include <vector>
#include <fstream>
#include "Ground.h"

class Player;

class World
{
public:
	World() {}
	virtual ~World();

	void loadTiles(const std::string& path);

	std::vector<Ground> m_tiles{};

	std::vector<Player*> m_players{};
};
