#pragma once

#include "ButtonUI.h"

class TextButtonUI : public ButtonUI
{
public:
	TextButtonUI(sf::Vector2f position = sf::Vector2f{ 0.f, 0.f }, const std::string& stateRelated = "", const std::string& buttonTextString = "", const sf::Font* font = nullptr);
	virtual ~TextButtonUI() = default;

	void init(sf::Vector2f position, const std::string& stateRelated, const std::string& buttonTextString, const sf::Font* font);

	void render(sf::RenderWindow& window) const;

	void update(bool onHover);

	const std::string& getStateRelated() const { return m_stateRelated; }

private:
	std::string m_stateRelated{};

	sf::Text m_buttonText{};
};
