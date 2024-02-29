#pragma once

#include "UI.h"

class BackgroundUI : public UI
{
public:
	BackgroundUI(const std::string& textureName = "", const std::string& texturePath = "", sf::Vector2f position = sf::Vector2f{0.f, 0.f}, sf::Vector2i size = sf::Vector2i{0, 0}, float scale = 1.f);
	virtual ~BackgroundUI() = default;

	void init(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, sf::Vector2i size, float scale = 1.f);
};
