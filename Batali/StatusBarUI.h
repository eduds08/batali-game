#pragma once

#include "UI.h"

class StatusBarUI : public UI
{
public:
	StatusBarUI(const std::string& textureName = "", const std::string& texturePath = "", sf::Vector2i size = sf::Vector2i{ 0, 0 });
	virtual ~StatusBarUI() = default;

	void init(const std::string& textureName, const std::string& texturePath, sf::Vector2i size);

	// Update the frame of the health bar sprite according to current entity's hp
	void update();

	void setEntityStatus(const int* entityStatus);

	const std::string& getDirection() { return m_direction; }

private:
	int m_entityTotalStatusFraction{};
	const int* m_entityStatus{ nullptr };

	std::string m_direction{};
};
