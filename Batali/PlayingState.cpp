#include "PlayingState.h"

#include "PlayerRenderComponent.h"
#include "PlayerAnimationComponent.h"
#include "PlayerCollisionComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerLaunchProjectilesComponent.h"

#include "BoxerState.h"
#include "FireKnightState.h"
#include "WindHashashinState.h"

PlayingState::PlayingState(sf::RenderWindow& window, float& deltaTime, const std::string& firstCharacter, const std::string& secondCharacter)
	: StateContext{ window }
	, m_deltaTime{ deltaTime }
	//, player{ std::make_unique<Player>(std::make_unique<PlayerRenderComponent>(), std::make_unique<PlayerCollisionComponent>(), std::make_unique<PlayerPhysicsComponent>(), std::make_unique<PlayerAttackComponent>(), std::make_unique<PlayerLaunchProjectilesComponent>(), std::make_unique<PlayerAnimationComponent>())}
{
	m_currentState = PLAYING_STATE;

	// Initialize View
	m_view = m_window.getDefaultView();

	m_world.init("./map/map.txt", firstCharacter, secondCharacter);

	// Initialize Player 1
	/*if (firstCharacter == "fire_knight")
	{
		player->initChosenCharacter(std::make_unique<FireKnightState>());
	}
	else if (firstCharacter == "wind_hashashin")
	{
		player->initChosenCharacter(std::make_unique<WindHashashinState>());
	}
	else if (firstCharacter == "boxer")
	{
		player->initChosenCharacter(std::make_unique<BoxerState>());
	}*/

	//// Initialize Player 2
	//if (secondCharacter == "fire_knight")
	//{
	//	m_characters.emplace_back(std::make_shared<FireKnight>(RIGHT_CHARACTER_FIRST_POSITION));
	//}
	//else if (secondCharacter == "wind_hashashin")
	//{
	//	m_characters.emplace_back(std::make_shared<WindHashashin>(RIGHT_CHARACTER_FIRST_POSITION));
	//}
	//else if (secondCharacter == "boxer")
	//{
	//	m_characters.emplace_back(std::make_shared<Boxer>(RIGHT_CHARACTER_FIRST_POSITION));
	//}

	//// Initialize each player's status
	//m_characterStatus.emplace_back(CharacterStatusUI{ firstCharacter + "Logo", "./assets/" + firstCharacter + "/logo.png", m_characters[0].get() });
	//m_characterStatus.emplace_back(CharacterStatusUI{ secondCharacter + "Logo", "./assets/" + secondCharacter + "/logo.png", m_characters[1].get(), true });

	// Initialize map
	//m_world.loadTiles("./map/map.txt");
	// 

	// Initialize animation thread
	//m_animationThread = std::thread(&PlayingState::updateTexturesAndAnimations, this);
}

PlayingState::~PlayingState()
{
	//m_animationThread.join();
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
		/*updateCollisions();

		for (auto& characterStatus : m_characterStatus)
		{
			characterStatus.update();
		}

		for (auto& character : m_characters)
		{
			character->update(m_deltaTime);
		}*/

		//player->update(m_window, m_world, m_deltaTime);
			
		for (const auto& player : m_world.m_players)
		{
			player->update(m_window, m_world, m_deltaTime);
		}

		//m_world.m_players[0]->update(m_window, m_world, m_deltaTime);

		updateView();
	}

	m_pressedKey = sf::Keyboard::Scancode::Unknown;
}

void PlayingState::render()
{
	/*for (auto& character : m_characters)
	{
		character->render(m_window, m_debugMode);
	}*/

	//player->render(m_window);
	for (const auto& player : m_world.m_players)
	{
		player->render(m_window);
	}
	//m_world.m_players[0]->render(m_window);

	// Render the tiles inside the view's limits
	for (auto& tile : m_world.m_tiles)
	{
		if (tile.getSprite().getPosition().x <= m_viewLimits[1] && tile.getSprite().getPosition().x >= m_viewLimits[3]
			&& tile.getSprite().getPosition().y >= m_viewLimits[0] && tile.getSprite().getPosition().y <= m_viewLimits[2])
		{
			m_window.draw(tile.getSprite());
		}
	}

	/*for (auto& characterStatus : m_characterStatus)
	{
		characterStatus.render(m_window);
	}*/
}

//void PlayingState::updateCollisions()
//{
//	// We reset isCollidingHorizontally to false for all actors, so when isColliding() is called, if the actor collides in the x-direction, it will be true.
//	// If doesn't collide, it remains false.
//	for (auto& character : m_characters)
//	{
//		character->setIsCollidingHorizontally(false);
//	}
//
//	// Player's collision with tiles
//	for (auto& tile : m_world.m_tiles)
//	{
//		for (auto& character : m_characters)
//		{
//			updateActorCollisionWithTiles(*character, tile);
//		}
//	}
//
//	// Player's collisions on each other (attack)
//	for (auto& attackingCharacter : m_characters)
//	{
//		for (auto& attackedCharacter : m_characters)
//		{
//			if (attackedCharacter != attackingCharacter)
//			{
//				// Attacked by hitbox
//				if (attackingCharacter->getStateName() == "AttackingState")
//				{
//					if (attackingCharacter->getCharacterState<AttackingState>()->checkAttack(*attackingCharacter, *attackedCharacter))
//					{
//						handleKnockbackMove(*attackingCharacter, *attackedCharacter, attackingCharacter->getCharacterState<AttackingState>()->m_attackHitbox->getIsUltimateActivate());
//					}
//				}
//
//				// Attacked by projectiles
//				if (dynamic_cast<CharacterWithProjectiles*>(attackingCharacter.get()) != nullptr)
//				{
//					for (auto& ultimateProjectile : dynamic_cast<CharacterWithProjectiles*>(attackingCharacter.get())->getProjectiles())
//					{
//						if (ultimateProjectile->getShape().getGlobalBounds().intersects(attackedCharacter->getShape().getGlobalBounds()))
//						{
//							ultimateProjectile->setCollided(true);
//
//							attackedCharacter->setState(new HittedState{ "FAST_HITTED", attackingCharacter.get() });
//						}
//					}
//				}
//			}
//		}
//	}
//}

//void PlayingState::updateActorCollisionWithTiles(ColliderActor& actor, Ground& tile)
//{
//	if (tile.getSprite().getPosition().x <= actor.getShapeLimits()[1] && tile.getSprite().getPosition().x >= actor.getShapeLimits()[3]
//		&& tile.getSprite().getPosition().y >= actor.getShapeLimits()[0] && tile.getSprite().getPosition().y <= actor.getShapeLimits()[2])
//	{
//		actor.updateCollisionWith(tile.getSprite());
//	}
//}
//
//void PlayingState::handleKnockbackMove(Character& attackingActor, Character& attackedActor, bool isUltimateActivate)
//{
//	float attackDirection = attackingActor.getShapePosition().x - attackedActor.getShapePosition().x;
//
//	if (!isUltimateActivate)
//	{
//		if (attackingActor.getCharacterState<AttackingState>()->m_attackHitbox->getDamage() != WIND_HASHASHIN_ULTIMATE_DAMAGE)
//		{
//			// Knockback of the attackedActor. The attackedActor will be pushed until it doesn't collide with the hitbox anymore or until it collides with a wall.
//			while (attackedActor.getShape().getGlobalBounds().intersects((attackingActor.getCharacterState<AttackingState>()->m_attackHitbox->getShape().getGlobalBounds())) && !attackedActor.getIsCollidingHorizontally())
//			{
//				for (auto& tile : m_world.m_tiles)
//				{
//					updateActorCollisionWithTiles(attackedActor, tile);
//				}
//				attackedActor.knockbackMove(m_deltaTime, attackDirection);
//			}
//		}
//	}
//}

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
//
//void PlayingState::updateTexturesAndAnimations()
//{
//	while (m_currentState == PLAYING_STATE)
//	{
//		if (!m_onPause)
//		{
//			// This thread's sleep controls the frames/seconds (fps) of the animations
//			std::this_thread::sleep_for(std::chrono::milliseconds(75));
//
//			for (auto& character : m_characters)
//			{
//				character->updateAnimation();
//			}
//		}
//	}
//}
