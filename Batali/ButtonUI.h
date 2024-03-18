#pragma once

#include "UI.h"

class ButtonUI : public UI
{
public:
	ButtonUI();
	virtual ~ButtonUI() = default;

	// Updates the frame of button sprite according to its "onHover state"
	virtual void update(bool onHover) = 0;

	virtual void render(sf::RenderWindow& window) const = 0;

	//const std::string& getStateRelated() const { return m_stateRelated; }

protected:
	/*std::string m_stateRelated{};

	sf::Text m_buttonText{};*/
};
