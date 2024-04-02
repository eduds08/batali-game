#include "ProjectileAnimationComponent.h"

#include "GameObject.h"

void ProjectileAnimationComponent::initTextures(GameObject& gameObject)
{
	for (auto& projectileAnimationName : m_projectileAnimationNames)
	{
		if (!m_texturesManager.loadTexture(gameObject.getName() + projectileAnimationName, "./assets/" + gameObject.getName() + "/" + projectileAnimationName + ".png"))
		{
			std::cout << "ERROR LOADING TEXTURE: " + gameObject.getName() + projectileAnimationName + "\n";
		}
	}
}

void ProjectileAnimationComponent::setNewAnimation(GameObject& gameObject, const std::string& name, bool isLooping)
{
	m_currentAnimation = m_texturesManager.createNewAnimation(name, PROJECTILE_SIZE, isLooping, gameObject.getName());
	gameObject.getSprite().setTexture(m_currentAnimation->getTexture());
	gameObject.getSprite().setTextureRect(m_currentAnimation->getCurrentTextureFrame());
}

void ProjectileAnimationComponent::update(GameObject& gameObject)
{
	m_currentAnimation->update();

	gameObject.getSprite().setTextureRect(m_currentAnimation->getCurrentTextureFrame());
}
