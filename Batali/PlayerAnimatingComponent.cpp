#include "PlayerAnimatingComponent.h"

#include "Player.h"

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
	if (m_currentAnimation == nullptr)
	{
		m_currentAnimation = m_texturesManager.createNewAnimation(IDLE_ANIMATION, { 288, 127 }, true, player.getName());
		player.getSprite().setTexture(m_currentAnimation->getTexture());
	}

	

	player.getSprite().setTextureRect(m_currentAnimation->getCurrentTextureFrame());
	
	m_currentAnimation->update();
}
