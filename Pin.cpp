#include "Pin.h"

Pin::Pin(Pin::State_t state)
{ 
	currentState = state; 
}

Pin::State_t Pin::GetState(void) const
{
	return this->currentState;
}