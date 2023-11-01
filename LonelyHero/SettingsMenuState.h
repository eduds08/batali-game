#pragma once

#include "MenuContext.h"

class SettingsMenuState : public MenuContext
{
public:
	SettingsMenuState(sf::RenderWindow& window, float& deltaTime);
	virtual ~SettingsMenuState() = default;

private:

};
