#pragma once

#include "IAnimationComponent.h"

#include "TexturesManager.h"
#include "AbstractAnimation.h"

#include "Constants.h"

using namespace constants;

class ProjectileAnimationComponent : public IAnimationComponent
{
public:
	ProjectileAnimationComponent() = default;
	virtual ~ProjectileAnimationComponent();

	virtual void initTextures(GameObject& gameObject);

	virtual void setNewAnimation(GameObject& gameObject, const std::string& name, bool isLooping);

	virtual AbstractAnimation* getCurrentAnimation() { return m_currentAnimation; }

	virtual void update(GameObject& gameObject);

private:
	TexturesManager& m_texturesManager{ TexturesManager::getInstance() };

	AbstractAnimation* m_currentAnimation{ nullptr };

	std::vector<std::string> m_projectileAnimationNames{ PROJECTILE_MOVING_ANIMATION, PROJECTILE_COLLISION_ANIMATION };

};
