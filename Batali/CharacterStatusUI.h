//#pragma once
//
//#include "UI.h"
//#include "StatusBarUI.h"
//#include "Character.h"
//
//class CharacterStatusUI : public UI
//{
//public:
//	CharacterStatusUI(const std::string& textureName = "", const std::string& texturePath = "", Character* character = nullptr, bool onRight = false);
//	virtual ~CharacterStatusUI() = default;
//
//	void init(const std::string& textureName, const std::string& texturePath, Character* character = nullptr, bool onRight = false);
//
//	void update();
//
//	void updatePosition(sf::Vector2f viewCenter, sf::Vector2f viewSize, bool onRight = false);
//
//	void render(sf::RenderWindow& window);
//
//private:
//	StatusBarUI m_healthBar{};
//};
