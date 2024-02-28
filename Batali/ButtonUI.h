#pragma once

#include "UI.h"

class ButtonUI : public UI
{
public:
	ButtonUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, const std::string& stateRelated);
	virtual ~ButtonUI() = default;

	// Updates the frame of button sprite according to its "onHover state"
	void update(bool onHover);

	const std::string& getStateRelated() { return m_stateRelated; }
private:
	const std::string m_stateRelated{};
};

