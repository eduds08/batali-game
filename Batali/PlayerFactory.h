#pragma once

#include <memory>
#include <string>

class Player;

class PlayerFactory
{
public:
	PlayerFactory() = default;
	virtual ~PlayerFactory() = default;

	std::unique_ptr<Player> createPlayer(const std::string& characterName);
private:
	std::unique_ptr<Player> createFireKnight();
	std::unique_ptr<Player> createWindHashashin();
	std::unique_ptr<Player> createBoxer();
};
