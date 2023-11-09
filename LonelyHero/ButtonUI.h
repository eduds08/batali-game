#pragma once

#include "UI.h"

class ButtonUI : public UI
{
public:
	ButtonUI(sf::Vector2f position, const std::string& textureName, const std::string& texturePath);
	virtual ~ButtonUI() = default;

	// Updates the frame of button sprite according to its "onHover state"
	void update(bool onHover);
private:

};

