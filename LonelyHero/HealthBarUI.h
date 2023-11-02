#pragma once

#include "UI.h"

class HealthBarUI : public UI
{
public:
	HealthBarUI(sf::Vector2f position, const std::string& textureName, const std::string& texturePath);
	virtual ~HealthBarUI() = default;

	void update();

	void setEntityHp(const int* entityHp);

private:
	int m_entityTotalHpFraction{};
	const int* m_entityHp{ nullptr };
};
