#include "JumpCommand.h"
#include "Character.h"

void JumpCommand::execute(Character& character)
{
	character.handleCondition("JUMP");
}
