#pragma once

#include "Pin.h"

class Input
{
private:
	Pin* connection;	// TODOPTR

public:
	Input(Pin* initialConnection = nullptr);

	bool IsConnected(void) const;
	Pin::State_t GetState(void) const;
	void Connect(Pin* connection);
	void Disonnect(void);
};

