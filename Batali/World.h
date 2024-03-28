#pragma once

#include <vector>
#include <fstream>
#include "Ground.h"

class World
{
public:
	World() {}
	virtual ~World() = default;

	void loadTiles(const std::string& path);

	std::vector<Ground> m_tiles{};
};
