#pragma once

#include "StateContext.h"
#include "TextButtonUI.h"
#include "ImageButtonUI.h"
#include <memory>

// Useful for states that uses buttons
class ButtonAuxState : public StateContext
{
public:
	ButtonAuxState(sf::RenderWindow& window);
	virtual ~ButtonAuxState() = default;

	void initTextButton(const std::string& text, sf::Vector2f position, const std::string& stateRelated);
	void initImageButton(sf::Vector2f position, const std::string& textureName, const std::string& texturePath);

	// Moves button, updates onHover, checks and handle button's press. isUpDown is related to button direction (up or down, right or left)
	void updateButtons(bool isUpDown);

	void renderButtons();

	// Called when user press enter on a button. It checks which button was pressed and then changes the current state according to it
	void pressTextButton(TextButtonUI& buttonPressed) { m_currentState = buttonPressed.getStateRelated(); }
	virtual void pressImageButton() {}

protected:
	std::vector<std::shared_ptr<ButtonUI>> m_buttons{};

	size_t m_onHoverButton{ 0 };
};
