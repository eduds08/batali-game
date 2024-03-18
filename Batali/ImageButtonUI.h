#pragma once

#include "ButtonUI.h"

class ImageButtonUI : public ButtonUI
{
public:
	ImageButtonUI(sf::Vector2f position = sf::Vector2f{ 0.f, 0.f }, const std::string& textureName = "", const std::string& texturePath = "");
	virtual ~ImageButtonUI() = default;

	void init(sf::Vector2f position, const std::string& textureName, const std::string& texturePath);

	void render(sf::RenderWindow& window) const;

	void update(bool onHover);

private:
	sf::RectangleShape m_buttonBorder{};

};
