#include "RollCommand.h"
#include "Character.h"

void RollCommand::execute(Character& character)
{
	character.handleCondition("ROLL");
}
