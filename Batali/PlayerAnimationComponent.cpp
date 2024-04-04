#include "PlayerAnimationComponent.h"

#include "Player.h"

PlayerAnimationComponent::PlayerAnimationComponent()
{
}

PlayerAnimationComponent::~PlayerAnimationComponent()
{
	if (m_currentAnimation)
	{
		delete m_currentAnimation;
		m_currentAnimation = nullptr;
	}
}

void PlayerAnimationComponent::initTextures(GameObject& gameObject)
{
	for (auto& playerAnimationName : m_playerAnimationNames)
	{
		if (!m_texturesManager.loadTexture(gameObject.getName() + playerAnimationName, "./assets/" + gameObject.getName() + "/" + playerAnimationName + ".png"))
		{
			std::cout << "ERROR LOADING TEXTURE: " + gameObject.getName() + playerAnimationName + "\n";
		}
	}
}

void PlayerAnimationComponent::setNewAnimation(GameObject& gameObject, const std::string& name, bool isLooping)
{
	m_currentAnimation = m_texturesManager.createNewAnimation(name, gameObject.getSpriteSize(), isLooping, gameObject.getName());
	gameObject.getSprite().setTexture(*m_currentAnimation->getTexture());
	gameObject.getSprite().setTextureRect(m_currentAnimation->getCurrentTextureFrame());
}

void PlayerAnimationComponent::update(GameObject& gameObject)
{
	m_currentAnimation->update();

	gameObject.getSprite().setTextureRect(m_currentAnimation->getCurrentTextureFrame());
}
