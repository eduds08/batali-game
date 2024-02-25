#pragma once

#include "ButtonAuxState.h"
#include "ButtonUI.h"

class MainMenuState : public ButtonAuxState
{
public:
	MainMenuState(sf::RenderWindow& window);
	virtual ~MainMenuState() = default;

	virtual void update();
	virtual void render();

private:
};
