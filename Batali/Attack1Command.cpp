#include "Attack1Command.h"
#include "Character.h"

void Attack1Command::execute(Character& character)
{
	character.handleCondition("ATTACK_1");
}
