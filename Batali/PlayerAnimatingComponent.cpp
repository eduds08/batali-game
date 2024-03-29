#include "PlayerAnimatingComponent.h"

#include "Player.h"

PlayerAnimatingComponent::PlayerAnimatingComponent()
{
}

PlayerAnimatingComponent::~PlayerAnimatingComponent()
{
}

void PlayerAnimatingComponent::update(Player& player)
{
	//if (rolling)
	//{
		m_currentAnimation = m_texturesManager.createNewAnimation("Rolling", { 288, 127 }, false);
		player.getSprite().setTexture(m_currentAnimation->getTexture());
		player.getSprite().setTextureRect(m_currentAnimation->getCurrentTextureFrame());
	//}


	// Ap�s todas as verifica��es para decidir qual anima��o aplicar:
		m_currentAnimation->update();
}
