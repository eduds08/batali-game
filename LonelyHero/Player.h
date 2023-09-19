#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "TexturesManager.h"

class Player
{
public:
	Player();
	~Player();

	void move();

	void update();

	sf::Sprite& getSprite() { return m_sprite; }

	// Criar uma classe base para os seguintes atributos depois:
	int textureFrameCount{ 0 };
	int frameWidth{ 120 };
	int frameHeight{ 80 };
	int frameAmount{ 10 };

	bool onFloor{ false };

private:
	sf::Sprite m_sprite{};

	bool m_isRunning{ false };
	int m_facingRight{ 1 };
	//bool onFloor{ false };

	
};

