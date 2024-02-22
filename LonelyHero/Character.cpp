#include "Character.h"

Character::Character(sf::Vector2f firstPosition, int playerNumber, bool isBot, sf::Vector2f* playerPosition)
	: SwordEntity{ firstPosition }
	, m_playerNumber{ playerNumber }
	, m_isBot{ isBot }
	, m_playerPosition{ playerPosition }
{
}