#include "CharacterWithProjectiles.h"

#include "DeadState.h"

CharacterWithProjectiles::CharacterWithProjectiles()
	: Character{}
{
}

void CharacterWithProjectiles::update(float& deltaTime)
{
	if (dynamic_cast<DeadState*>(m_state) == nullptr)
	{
		updateCharacterWithProjectiles(deltaTime);
	}

	Character::update(deltaTime);
}

void CharacterWithProjectiles::updateCharacterWithProjectiles(float& deltaTime)
{
	std::vector<std::vector<std::shared_ptr<Projectile>>::iterator> collidedProjectiles{};

	for (std::vector<std::shared_ptr<Projectile>>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); ++it)
	{
		(*it)->update(deltaTime);

		if ((*it)->getVanished())
		{
			collidedProjectiles.emplace_back(it);
		}
	}

	for (int i = 0; i < collidedProjectiles.size(); ++i)
	{
		m_projectiles.erase(collidedProjectiles[i]);
	}
}

void CharacterWithProjectiles::render(sf::RenderWindow& window, bool debugMode)
{
	Character::render(window, debugMode);

	if (m_projectiles.size() > 0)
	{
		for (auto& projectile : m_projectiles)
		{
			window.draw(projectile->getSprite());

			if (debugMode)
			{
				window.draw(projectile->getShape());
			}
		}
	}
}

void CharacterWithProjectiles::updateAnimation()
{
	AnimatedActor::updateAnimation();

	if (m_projectiles.size() > 0)
	{
		for (auto& projectile : m_projectiles)
		{
			projectile->updateAnimation();
		}
	}
}
