#include "Game.h"

bool Game::isRunning = true;

Game::Game()
{
	init();
}

Game::~Game()
{
}

void Game::init()
{
	m_window.setView(m_view);
	loadAndCreateMap("./map.txt");
	playerAnimationThread = std::thread(&Game::updateTexturesAndAnimations, this);
	run();
}

void Game::update()
{
	m_player.update(m_deltaTime);
	m_enemy.update(m_deltaTime);
	updateCollision();
	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);
}

void Game::render()
{
	m_window.clear();

	m_window.draw(m_player.getShape());
	m_window.draw(m_player.getSprite());

	m_window.draw(m_enemy.getShape());
	m_window.draw(m_enemy.getSprite());

	for (auto& ground : grounds)
	{
		m_window.draw(ground.getSprite());
	}

	m_window.display();
}

void Game::run()
{
	while (m_window.isOpen())
	{
		m_deltaTime = m_clock.restart().asSeconds();

		if (m_deltaTime > 1.f / 20.f)
		{
			m_deltaTime = { 1.f / 20.f };
		}

		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
			{
				Game::isRunning = false;
				m_window.close();
			}
		}

		update();
		render();
	}

	playerAnimationThread.join();
}

void Game::updateCollision()
{
	for (auto& ground : grounds)
	{
		if (m_player.isColliding(ground.getSprite()))
		{
			m_player.handleCollision();
			m_player.checkIfCanJump();
		}
		if (m_enemy.isColliding(ground.getSprite()))
		{
			m_enemy.handleCollision();
		}
	}
}

void Game::loadAndCreateMap(const std::string& mapFilePath)
{
	std::fstream mapFile{ mapFilePath, std::ios::in };
	std::string row{};

	int x{ 0 };
	int y{ 0 };

	std::string a{};

	while (std::getline(mapFile, row))
	{
		for (int i = 0; i < 40; i++)
		{
			mapFile >> a;
			if (a != "0")
			{
				grounds.emplace_back(Ground{ 16, 16, sf::Vector2f{x * 16.f + 8.f, y * 16.f + 8.f}, a,  "./tiles/" + a + ".png" });
			}
			++x;
		}
		
		x = 0;
		y++;
	}

	mapFile.close();
}

void Game::updateTexturesAndAnimations()
{
	while (Game::isRunning)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		m_player.updateTextureAndAnimation();
		m_enemy.updateTextureAndAnimation();
	}
	
}
