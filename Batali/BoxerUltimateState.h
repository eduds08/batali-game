#pragma once

#include "IProjectileTypeState.h"

class BoxerUltimateState : public IProjectileTypeState
{
public:
	BoxerUltimateState() = default;
	virtual ~BoxerUltimateState() = default;

	virtual const std::string& getName() const { return m_name; }

	virtual void setSpriteSize(Projectile& projectile);
	virtual void setShapeSize(Projectile& projectile);

private:
	const std::string m_name{ "boxer_ultimate" };
};
