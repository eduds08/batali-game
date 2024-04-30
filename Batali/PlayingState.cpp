#include "PlayingState.h"


PlayingState::PlayingState(sf::RenderWindow& window, float& deltaTime, const std::string& firstCharacter, const std::string& secondCharacter)
	: StateContext{ window }
	, m_deltaTime{ deltaTime }
{
	m_currentState = PLAYING_STATE;

	// Initialize View
	m_view = m_window.getDefaultView();
	m_view.zoom(0.6f);

	m_world.init("./map/map.txt", firstCharacter, secondCharacter);

	//// Initialize each player's status
	//m_characterStatus.emplace_back(CharacterStatusUI{ firstCharacter + "Logo", "./assets/" + firstCharacter + "/logo.png", m_characters[0].get() });
	//m_characterStatus.emplace_back(CharacterStatusUI{ secondCharacter + "Logo", "./assets/" + secondCharacter + "/logo.png", m_characters[1].get(), true });
}

PlayingState::~PlayingState()
{
}

void PlayingState::update()
{
	if (m_pressedKey == sf::Keyboard::Scancode::P)
	{
		m_onPause = !m_onPause;
	}

	if (m_pressedKey == sf::Keyboard::Scancode::T)
	{
		m_debugMode = !m_debugMode;
	}
	
	if (!m_onPause)
	{
		/*
		for (auto& characterStatus : m_characterStatus)
		{
			characterStatus.update();
		}
		*/
			
		for (const auto& player : m_world.m_players)
		{
			player->update(m_window, m_world, m_deltaTime);
		}

		updateView();
	}

	m_pressedKey = sf::Keyboard::Scancode::Unknown;
}

void PlayingState::render()
{
	//player->render(m_window);
	for (const auto& player : m_world.m_players)
	{
		player->render(m_window);
	}

	// Render the tiles inside the view's limits
	for (auto& tile : m_world.m_tiles)
	{
		if (tile.getSprite().getPosition().x <= m_viewLimits[1] && tile.getSprite().getPosition().x >= m_viewLimits[3]
			&& tile.getSprite().getPosition().y >= m_viewLimits[0] && tile.getSprite().getPosition().y <= m_viewLimits[2])
		{
			m_window.draw(tile.getSprite());
		}
	}

	/*
	for (auto& characterStatus : m_characterStatus)
	{
		characterStatus.render(m_window);
	}
	*/
}

void PlayingState::updateView()
{
	m_view.setCenter(m_world.m_players[0]->getShape().getPosition());
	m_window.setView(m_view);

	/*m_characterStatus[0].updatePosition(m_view.getCenter(), m_view.getSize());
	m_characterStatus[1].updatePosition(m_view.getCenter(), m_view.getSize(), true);*/

	// 0 -> top, 1 -> right, 2 -> bottom, 3 -> left
	m_viewLimits[0] = m_view.getCenter().y - m_view.getSize().y / 2.f - TILE_SIZE_FLOAT;
	m_viewLimits[1] = m_view.getCenter().x + m_view.getSize().x / 2.f + TILE_SIZE_FLOAT;
	m_viewLimits[2] = m_view.getCenter().y + m_view.getSize().y / 2.f + TILE_SIZE_FLOAT;
	m_viewLimits[3] = m_view.getCenter().x - m_view.getSize().x / 2.f - TILE_SIZE_FLOAT;
}
