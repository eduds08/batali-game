#include "PlayerPhysicsComponent.h"
#include "Player.h"

PlayerPhysicsComponent::PlayerPhysicsComponent()
{
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}

void PlayerPhysicsComponent::update(Player& player, World& world, float& deltaTime)
{
	m_isCollidingHorizontally = false;

	// Collision with tiles
	for (auto& tile : world.m_tiles)
	{
		if (tile.getSprite().getPosition().x <= m_shapeLimits[1] && tile.getSprite().getPosition().x >= m_shapeLimits[3]
			&& tile.getSprite().getPosition().y >= m_shapeLimits[0] && tile.getSprite().getPosition().y <= m_shapeLimits[2])
		{
			updateCollisionWith(player, tile.getSprite());
		}
	}

	updateLimits(player);
}

void PlayerPhysicsComponent::updateCollisionWith(Player& player, const sf::Sprite& other)
{
	float otherHalfSizeX = other.getTexture()->getSize().x / 2.f;
	float otherHalfSizeY = other.getTexture()->getSize().y / 2.f;
	float otherPositionX = other.getPosition().x;
	float otherPositionY = other.getPosition().y;

	float thisHalfSizeX = player.getShape().getSize().x / 2.f;
	float thisHalfSizeY = player.getShape().getSize().y / 2.f;
	float thisPositionX = player.getShape().getPosition().x;
	float thisPositionY = player.getShape().getPosition().y;

	float deltaX = otherPositionX - thisPositionX;
	float deltaY = otherPositionY - thisPositionY;

	float intersectX = abs(deltaX) - (otherHalfSizeX + thisHalfSizeX);
	float intersectY = abs(deltaY) - (otherHalfSizeY + thisHalfSizeY);

	if (intersectX < 0.f && intersectY < 0.f)
	{
		if (intersectX > intersectY) {

			if (deltaX > 0.f)
			{
				player.getShape().move(sf::Vector2f{ intersectX, 0.f });
				m_collisionDirection.x = 1.0f;
			}
			else
			{
				player.getShape().move(sf::Vector2f{ -intersectX, 0.f });
				m_collisionDirection.x = -1.0f;
			}
			m_isCollidingHorizontally = true;
			m_collisionDirection.y = 0.f;
		}
		else
		{
			if (deltaY > 0.f)
			{
				player.getShape().move(sf::Vector2f{ 0.f, intersectY });
				m_collisionDirection.y = 1.0f;
			}
			else
			{
				player.getShape().move(sf::Vector2f{ 0.f, -intersectY });
				m_collisionDirection.y = -1.0f;
			}
			m_collisionDirection.x = 0.f;
		}

		handleCollision(player);
	}
}

void PlayerPhysicsComponent::handleCollision(Player& player)
{
	// Sets m_velocity.y to 0 if actor collides in bottom or top
	if (m_collisionDirection.y != 0.f)
	{
		m_velocity.y = 0.f;
	}

	// Sets knockbackVelocity to 0 if actor is pushed against a wall after being attacked
	if (m_isCollidingHorizontally)
	{
		m_knockbackVelocity = 0.f;
	}
}

void PlayerPhysicsComponent::updateLimits(Player& player)
{
	// Limit is set to TILES_PHYSICAL_ACTOR_LIMIT tiles in each direction (top, right, bottom left) from the center of actor's shape

	m_shapeLimits[0] = player.getShape().getPosition().y - TILES_PHYSICAL_ACTOR_LIMIT * TILE_SIZE_FLOAT;	// TOP
	m_shapeLimits[1] = player.getShape().getPosition().x + TILES_PHYSICAL_ACTOR_LIMIT * TILE_SIZE_FLOAT;	// RIGHT
	m_shapeLimits[2] = player.getShape().getPosition().y + TILES_PHYSICAL_ACTOR_LIMIT * TILE_SIZE_FLOAT;	// BOTTOM
	m_shapeLimits[3] = player.getShape().getPosition().x - TILES_PHYSICAL_ACTOR_LIMIT * TILE_SIZE_FLOAT;	// LEFT
}
