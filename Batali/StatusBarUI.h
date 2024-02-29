#pragma once

#include "UI.h"

class StatusBarUI : public UI
{
public:
	StatusBarUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, sf::Vector2i size);
	virtual ~StatusBarUI() = default;

	// Update the frame of the health bar sprite according to current entity's hp
	void update();

	void setEntityStatus(const int* entityStatus);

	const std::string& getDirection() { return m_direction; }
	
	void flipSprite() { m_sprite.setScale(-1.f, 1.f); }

private:
	int m_entityTotalStatusFraction{};
	const int* m_entityStatus{ nullptr };

	std::string m_direction{};
};
