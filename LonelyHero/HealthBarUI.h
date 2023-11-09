#pragma once

#include "UI.h"

class HealthBarUI : public UI
{
public:
	HealthBarUI(sf::Vector2f position, const std::string& textureName, const std::string& texturePath, const int* entityHp);
	virtual ~HealthBarUI() = default;

	// Update the frame of the health bar sprite according to current entity's hp
	void update();

private:
	int m_entityTotalHpFraction{};
	const int* m_entityHp{ nullptr };
};
