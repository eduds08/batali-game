#pragma once

#include <string>
#include <memory>
#include "AbstractAnimation.h"
class GameObject;

class IAnimationComponent
{
public:
	virtual ~IAnimationComponent() = default;

	virtual void initTextures(GameObject& gameObject) = 0;

	virtual void setNewAnimation(GameObject& gameObject, const std::string& name, bool isLooping) = 0;

	virtual std::unique_ptr<AbstractAnimation>& getCurrentAnimation() = 0;

	virtual void update(GameObject& gameObject) = 0;
};
