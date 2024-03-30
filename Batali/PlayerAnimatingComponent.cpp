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

void PlayerAnimatingComponent::update(Player& player)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(60));

	if (m_currentAnimation == nullptr || m_currentAnimation->getName() != player.animationName)
	{
		m_currentAnimation = m_texturesManager.createNewAnimation(player.animationName, { 288, 127 }, true, player.getName());
		player.getSprite().setTexture(m_currentAnimation->getTexture());
	}

	player.getSprite().setTextureRect(m_currentAnimation->getCurrentTextureFrame());
	
	m_currentAnimation->update();
}
