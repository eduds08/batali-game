#pragma once

class IAnimation
{
public:
	virtual ~IAnimation() = default;

	virtual void update() = 0;
};
