#pragma once

#include "Pin.h"

class Input
{
private:
	Pin* connection;

public:
	Input(Pin* initialConnection = nullptr);
	/* Sprawdzenie czy input jest po��czony */
	bool IsConnected(void) const;
	/* Zwraca stan na podstawie po��czengo outputu */
	Pin::State_t GetState(void) const;
	/* Modyfikuje element connection */
	void Connect(Pin* connection);
	void Disonnect(void);
};

