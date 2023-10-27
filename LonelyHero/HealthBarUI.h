#pragma once

#include "UI.h"
#include <memory>

class HealthBarUI : public UI
{
public:
	HealthBarUI(sf::Vector2f position, const std::string& textureName, const std::string& texturePath);
	virtual ~HealthBarUI() = default;

	void updateHealthBar();

	void setEntityHp(const int* entityHp);

private:
	int m_entityTotalHpFraction{};
	const int* m_entityHp{ nullptr };
};
