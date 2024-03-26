#include "RunCommand.h"
#include "Character.h"

void RunCommand::execute(Character& character)
{
	character.handleCondition("RUN");
}
