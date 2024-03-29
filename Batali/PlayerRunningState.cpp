#include "PlayerRunningState.h"

#include "Player.h"

PlayerRunningState::PlayerRunningState()
{

}

PlayerRunningState::~PlayerRunningState()
{

}

IPlayerState* PlayerRunningState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerRunningState::update(Player& player)
{
	player.getVelocity().x = 200.f * player.m_facingRight;
}

void PlayerRunningState::enter(Player& player)
{

}
