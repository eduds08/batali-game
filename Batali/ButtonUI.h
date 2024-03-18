#pragma once

#include "UI.h"

class ButtonUI : public UI
{
public:
	ButtonUI(sf::Vector2f position = sf::Vector2f{0.f, 0.f}, const std::string& stateRelated = "", const std::string& buttonTextString = "", const sf::Font* font = nullptr);
	virtual ~ButtonUI() = default;

	void init(sf::Vector2f position, const std::string& stateRelated, const std::string& buttonTextString, const sf::Font* font);

	// Updates the frame of button sprite according to its "onHover state"
	void update(bool onHover);

	void render(sf::RenderWindow& window) const;

	const std::string& getStateRelated() const { return m_stateRelated; }

private:
	std::string m_stateRelated{};

	sf::Text m_buttonText{};
};
