#include "PlayerAnimatingComponent.h"

#include "Player.h"

#include <chrono>
#include <thread>

PlayerAnimatingComponent::PlayerAnimatingComponent()
{
}

PlayerAnimatingComponent::~PlayerAnimatingComponent()
{
}

void PlayerAnimatingComponent::initTextures(Player& player)
{
	for (auto& playerAnimationName : m_playerAnimationNames)
	{
		if (!m_texturesManager.loadTexture(player.getName() + playerAnimationName, "./assets/" + player.getName() + "/" + playerAnimationName + ".png"))
		{
			std::cout << "ERROR LOADING TEXTURE: " + player.getName() + playerAnimationName + "\n";
		}
	}
}

void PlayerAnimatingComponent::setNewAnimation(Player& player, const std::string& name, bool isLooping)
{
	m_currentAnimation = m_texturesManager.createNewAnimation(name, { 288, 127 }, isLooping, player.getName());
	player.getSprite().setTexture(m_currentAnimation->getTexture());
	player.getSprite().setTextureRect(m_currentAnimation->getCurrentTextureFrame());
}

void PlayerAnimatingComponent::update(Player& player)
{
	m_currentAnimation->update();
	
	player.getSprite().setTextureRect(m_currentAnimation->getCurrentTextureFrame());
}
