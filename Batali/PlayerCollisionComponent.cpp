#include "PlayerCollisionComponent.h"
#include "Player.h"

#include "PlayerAttackComponent.h"

#include "World.h"

PlayerCollisionComponent::PlayerCollisionComponent()
{
}

PlayerCollisionComponent::~PlayerCollisionComponent()
{
}

void PlayerCollisionComponent::update(GameObject& gameObject, World& world, float& deltaTime)
{
	m_isCollidingHorizontally = false;

	// Collision with tiles
	for (auto& tile : world.m_tiles)
	{
		if (tile.getSprite().getPosition().x <= m_shapeLimits[1] && tile.getSprite().getPosition().x >= m_shapeLimits[3]
			&& tile.getSprite().getPosition().y >= m_shapeLimits[0] && tile.getSprite().getPosition().y <= m_shapeLimits[2])
		{
			updateCollisionWith(gameObject, tile.getSprite());
		}
	}

	updateLimits(gameObject);

	m_knockbackVelocity = KNOCKBACK_SPEED;

	for (auto& enemy : world.m_players)
	{
		if (enemy->getId() != gameObject.getId())
		{
			if (gameObject.getShape().getGlobalBounds().intersects(enemy->getAttackComponent()->getAttackHitbox().getShape().getGlobalBounds()))
			{
				std::cout << "tookDamage\n";
				//takeDamage
				//knockback
			}
		}
	}
}

void PlayerCollisionComponent::updateCollisionWith(GameObject& gameObject, const sf::Sprite& other)
{
	float otherHalfSizeX = other.getTexture()->getSize().x / 2.f;
	float otherHalfSizeY = other.getTexture()->getSize().y / 2.f;
	float otherPositionX = other.getPosition().x;
	float otherPositionY = other.getPosition().y;

	float thisHalfSizeX = gameObject.getShape().getSize().x / 2.f;
	float thisHalfSizeY = gameObject.getShape().getSize().y / 2.f;
	float thisPositionX = gameObject.getShape().getPosition().x;
	float thisPositionY = gameObject.getShape().getPosition().y;

	float deltaX = otherPositionX - thisPositionX;
	float deltaY = otherPositionY - thisPositionY;

	float intersectX = abs(deltaX) - (otherHalfSizeX + thisHalfSizeX);
	float intersectY = abs(deltaY) - (otherHalfSizeY + thisHalfSizeY);

	if (intersectX < 0.f && intersectY < 0.f)
	{
		if (intersectX > intersectY) {

			if (deltaX > 0.f)
			{
				gameObject.getShape().move(sf::Vector2f{ intersectX, 0.f });
				m_collisionDirection.x = 1.0f;
			}
			else
			{
				gameObject.getShape().move(sf::Vector2f{ -intersectX, 0.f });
				m_collisionDirection.x = -1.0f;
			}
			m_isCollidingHorizontally = true;
			m_collisionDirection.y = 0.f;
		}
		else
		{
			if (deltaY > 0.f)
			{
				gameObject.getShape().move(sf::Vector2f{ 0.f, intersectY });
				m_collisionDirection.y = 1.0f;
			}
			else
			{
				gameObject.getShape().move(sf::Vector2f{ 0.f, -intersectY });
				m_collisionDirection.y = -1.0f;
			}
			m_collisionDirection.x = 0.f;
		}

		handleCollision(gameObject);
	}
}

void PlayerCollisionComponent::handleCollision(GameObject& gameObject)
{
	// Sets m_velocity.y to 0 if actor collides in bottom or top
	if (m_collisionDirection.y != 0.f)
	{
		gameObject.getVelocity().y = 0.f;
	}

	// Sets knockbackVelocity to 0 if actor is pushed against a wall after being attacked
	if (m_isCollidingHorizontally)
	{
		m_knockbackVelocity = 0.f;
	}
}

void PlayerCollisionComponent::updateLimits(GameObject& gameObject)
{
	// Limit is set to TILES_PHYSICAL_ACTOR_LIMIT tiles in each direction (top, right, bottom left) from the center of actor's shape

	m_shapeLimits[0] = gameObject.getShape().getPosition().y - TILES_PHYSICAL_ACTOR_LIMIT * TILE_SIZE_FLOAT;	// TOP
	m_shapeLimits[1] = gameObject.getShape().getPosition().x + TILES_PHYSICAL_ACTOR_LIMIT * TILE_SIZE_FLOAT;	// RIGHT
	m_shapeLimits[2] = gameObject.getShape().getPosition().y + TILES_PHYSICAL_ACTOR_LIMIT * TILE_SIZE_FLOAT;	// BOTTOM
	m_shapeLimits[3] = gameObject.getShape().getPosition().x - TILES_PHYSICAL_ACTOR_LIMIT * TILE_SIZE_FLOAT;	// LEFT
}

void PlayerCollisionComponent::knockbackMove(GameObject& gameObject, float& deltaTime, float attackDirection)
{
	if (attackDirection < 0.f)
	{
		// attack coming from left
		gameObject.getShape().move(sf::Vector2f{ m_knockbackVelocity, 0.f } *deltaTime);
	}
	else
	{
		// attack coming from right
		gameObject.getShape().move(sf::Vector2f{ m_knockbackVelocity * -1.f, 0.f } *deltaTime);
	}

	gameObject.getSprite().setPosition(sf::Vector2f{ gameObject.getShape().getPosition().x, gameObject.getShape().getPosition().y - (gameObject.getSprite().getTextureRect().getSize().y - gameObject.getShape().getSize().y) / 2.f});
}
