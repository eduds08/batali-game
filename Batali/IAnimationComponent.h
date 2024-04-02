#pragma once

#include <string>

class AbstractAnimation;
class GameObject;

class IAnimationComponent
{
public:
	virtual ~IAnimationComponent() = default;

	virtual void initTextures(GameObject& gameObject) = 0;

	virtual void setNewAnimation(GameObject& gameObject, const std::string& name, bool isLooping) = 0;

	virtual AbstractAnimation* getCurrentAnimation() = 0;

	virtual void update(GameObject& gameObject) = 0;
};
