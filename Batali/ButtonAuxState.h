#pragma once

#include "StateContext.h"
#include "ButtonUI.h"

// Useful for states that uses buttons
class ButtonAuxState : public StateContext
{
public:
	ButtonAuxState(sf::RenderWindow& window);
	virtual ~ButtonAuxState() = default;

	// Used once on constructor to create the menu buttons
	void initButton(const std::string& text, sf::Vector2f position, const std::string& stateRelated);

	// If isUpDown == true, use up and down keys, otherwise, use right and left keys
	void updateButtons(bool isUpDown);

	void renderButtons();

	// Called when user press enter on a button. It checks which button was pressed and then changes the current state according to it
	void pressButton(ButtonUI buttonPressed);

protected:
	std::vector<ButtonUI> m_buttons{};

	size_t m_onHoverButton{ 0 };
};
