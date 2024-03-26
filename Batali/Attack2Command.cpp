#include "Attack2Command.h"
#include "Character.h"

void Attack2Command::execute(Character& character)
{
	character.handleCondition("ATTACK_2");
}
