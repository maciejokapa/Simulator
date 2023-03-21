#include "GeneralOutput.h"


GeneralOutput::State_t GeneralOutput::GetState(void)
{
	return this->currentState;
}

GeneralOutput::GeneralOutput(GeneralOutput::State_t state)
{ 
	currentState = state; 
}