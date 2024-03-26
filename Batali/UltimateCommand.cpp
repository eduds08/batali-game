#include "UltimateCommand.h"
#include "Character.h"

void UltimateCommand::execute(Character& character)
{
	character.handleCondition("ULTIMATE");
}
