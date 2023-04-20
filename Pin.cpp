#include "Pin.h"

Pin::State_t Pin::GetState(void) const
{
	return this->currentState;
}

Pin::Pin(Pin::State_t state)
{ 
	currentState = state; 
}