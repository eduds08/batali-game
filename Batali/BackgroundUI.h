#pragma once

#include "UI.h"

class BackgroundUI : public UI
{
public:
	BackgroundUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, sf::Vector2i spriteSize, float scale = 1.f);
	virtual ~BackgroundUI() = default;
private:

};
