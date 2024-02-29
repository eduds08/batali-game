#pragma once

#include "UI.h"

class ButtonUI : public UI
{
public:
	ButtonUI(const std::string& textureName = "", const std::string& texturePath = "", sf::Vector2f position = sf::Vector2f{0.f, 0.f}, const std::string& stateRelated = "");
	virtual ~ButtonUI() = default;

	void init(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, const std::string& stateRelated);

	// Updates the frame of button sprite according to its "onHover state"
	void update(bool onHover);

	const std::string& getStateRelated() const { return m_stateRelated; }
private:
	std::string m_stateRelated{};
};

