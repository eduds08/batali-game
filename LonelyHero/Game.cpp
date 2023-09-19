#include "Game.h"

sf::Clock Game::clock{};

Game::Game()
	: m_window{ sf::VideoMode(600, 600), "Lonely Hero" }
	, m_event{}
	, m_player{}
	, m_elapsed{}
{

	sf::Texture dirtTexture{};
	dirtTexture.loadFromFile("./dirt.png");
	sf::Sprite dirt{ dirtTexture };
	std::vector<sf::Sprite> dirts{};
	std::vector<sf::FloatRect> dirtsBound{};
	std::vector<sf::Sprite>::iterator it;
	std::vector<sf::FloatRect>::iterator it2;
	
	for (int i = 0; i < 600; i += 10)
	{
	    dirt.setPosition(float(i), 540.f);
	    dirts.push_back(dirt);
	    dirtsBound.push_back(dirt.getGlobalBounds());
	}

	while (m_window.isOpen())
	{
		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}

		m_player.update();

		m_elapsed = Game::clock.getElapsedTime();

		if (m_elapsed.asSeconds() > 0.15f)
		{
			AnimationManager::animateSprite(m_player.getSprite(), m_player.frameAmount, m_player.frameWidth, m_player.frameHeight, m_player.textureFrameCount);
			Game::clock.restart();
		}

		m_player.onFloor = false;
		for (it2 = dirtsBound.begin(); it2 != dirtsBound.end(); it2++)
		{
			if (m_player.getSprite().getGlobalBounds().intersects(*it2))
			{
				m_player.onFloor = true;
			}
		}

		if (!m_player.onFloor)
		{
			m_player.getSprite().move(0.f, 9.81f * 0.07f);
		}
		
		m_window.clear();

		m_window.draw(m_player.getSprite());

		for (it = dirts.begin(); it != dirts.end(); it++)
		{
			m_window.draw(*it);
		}

		m_window.display();
	}
}

Game::~Game()
{
}
