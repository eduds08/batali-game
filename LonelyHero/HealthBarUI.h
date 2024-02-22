#pragma once

#include "UI.h"

class HealthBarUI : public UI
{
public:
	HealthBarUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position = sf::Vector2f{ 0.f, 0.f }, const int* entityHp = nullptr);
	virtual ~HealthBarUI() = default;

	// Update the frame of the health bar sprite according to current entity's hp
	void update();

	void setEntityHp(const int* entityHp);

private:
	int m_entityTotalHpFraction{};
	const int* m_entityHp{ nullptr };
};
