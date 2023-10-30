#pragma once

#include "MenuContext.h"

class PlayingState : public MenuContext
{
public:
	PlayingState(sf::RenderWindow& window, float& deltaTime);
	virtual ~PlayingState();

	virtual void update();
	virtual void render();

	void updateCollision();

	// Checks the collision of entity with the tiles that are inside its imaginary view.
	void updateEntityCollisionWithGrounds(MovableEntity& entity, Ground& ground);

	// Calls takeDamage and also knockbackMove for the attacked entity
	void handleEntityAttacked(SwordEntity& attackingEntity, DamageEntity& attackedEntity);
	
	void updateView();

	// Reads a .txt file to generate the tiles
	void loadAndCreateMap(const std::string& mapFilePath);

	// Thread method to run all animations
	void updateTexturesAndAnimations();

	void setOnPlayingState(bool onPlayingState) { m_onPlayingState = onPlayingState; }

private:
	HealthBarUI m_playerHealthBar{ sf::Vector2f{0.f, 0.f}, "playerHealthBar", "./assets/ui/playerHealthBar.png" };
	HealthBarUI m_enemyHealthBar{ sf::Vector2f{0.f, 0.f}, "enemyHealthBar", "./assets/ui/enemyHealthBar.png" };

	Player m_player{ playerFirstPosition };
	std::vector<Enemy> enemies{};
	std::vector<Ground> grounds{};
	
	std::thread animationThread;

	float m_rightViewLimit{};
	float m_leftViewLimit{};
	float m_topViewLimit{};
	float m_bottomViewLimit{};

	bool m_onPlayingState{ true }; // pode ser removido e usar o nome do state instead
};
