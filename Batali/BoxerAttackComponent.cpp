#include "BoxerAttackComponent.h"

#include "Player.h"
#include "BoxerUltimateState.h"

void BoxerAttackComponent::update(World& world, float& deltaTime)
{
	for (std::vector<std::unique_ptr<Projectile>>::iterator it = m_projectiles.begin(); it != m_projectiles.end();)
	{
		(*it)->update(world, deltaTime);

		if ((*it)->getVanished())
		{
			it = m_projectiles.erase(it);
		}
		else
		{
			++it;
		}
	}

	PlayerAttackComponent::update(world, deltaTime);
}

void BoxerAttackComponent::render(sf::RenderWindow& window)
{
	for (const auto& projectile : m_projectiles)
	{
		projectile->render(window);
	}
}

void BoxerAttackComponent::launchProjectile(std::unique_ptr<IProjectileTypeState> projectileTypeState)
{
	m_projectiles.emplace_back(std::make_unique<Projectile>(m_thisPlayer->getShape().getPosition() + BOXER_PROJECTILE_OFFSET_POSITION, static_cast<float>(m_thisPlayer->getFacingRight()), std::move(projectileTypeState), *m_thisPlayer));
}

void BoxerAttackComponent::updateAttack1(const int currentPlayerAnimationFrame)
{
	m_attackHitbox.setShapePosition(m_thisPlayer->getShape().getPosition() + sf::Vector2f{ 0.f, -15.f });

	if (currentPlayerAnimationFrame >= BOXER_ATTACK_1_STARTING_FRAME && currentPlayerAnimationFrame <= BOXER_ATTACK_1_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(BOXER_ATTACK_1_WIDTH, BOXER_ATTACK_1_HEIGHT);
		m_attackHitbox.setDamage(BOXER_ATTACK_1_DAMAGE);
	}
}

void BoxerAttackComponent::updateAttack2(const int currentPlayerAnimationFrame)
{
	m_attackHitbox.setShapePosition(m_thisPlayer->getShape().getPosition() + sf::Vector2f{ 16.f * static_cast<float>(m_thisPlayer->getFacingRight()), -28.f });

	if (currentPlayerAnimationFrame >= BOXER_ATTACK_2_STARTING_FRAME && currentPlayerAnimationFrame <= BOXER_ATTACK_2_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(BOXER_ATTACK_2_WIDTH, BOXER_ATTACK_2_HEIGHT);
		m_attackHitbox.setDamage(BOXER_ATTACK_2_DAMAGE);
	}
}

void BoxerAttackComponent::updateAirAttack(const int currentPlayerAnimationFrame)
{
	m_attackHitbox.setShapePosition(m_thisPlayer->getShape().getPosition() + sf::Vector2f{ 0.f, -20.f });

	if (currentPlayerAnimationFrame >= BOXER_AIR_ATTACK_STARTING_FRAME && currentPlayerAnimationFrame <= BOXER_AIR_ATTACK_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(BOXER_AIR_ATTACK_WIDTH, BOXER_AIR_ATTACK_HEIGHT);
		m_attackHitbox.setDamage(BOXER_AIR_ATTACK_DAMAGE);
	}
}

void BoxerAttackComponent::updateUltimate(const int currentPlayerAnimationFrame)
{
	if (currentPlayerAnimationFrame == BOXER_ULTIMATE_PT_1_FRAME)
	{
		if (m_projectiles.size() == 0)
		{
			launchProjectile(std::make_unique<BoxerUltimateState>());
		}
	}
	else if (currentPlayerAnimationFrame == BOXER_ULTIMATE_PT_2_FRAME)
	{
		if (m_projectiles.size() == 1)
		{
			launchProjectile(std::make_unique<BoxerUltimateState>());
		}
	}
}

void BoxerAttackComponent::attack(Player& enemy)
{
	float attackDirection = m_thisPlayer->getShape().getPosition().x - enemy.getShape().getPosition().x;
	enemy.setKnockbackVelocity(KNOCKBACK_SPEED * (-attackDirection / abs(attackDirection)));
	enemy.setDamageToTake(m_attackHitbox.getDamage());
	enemy.handleCondition("HITTED");
}
