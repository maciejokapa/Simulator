#pragma once

#include "GeneralOutput.h"

class Input
{
private:

	GeneralOutput* connection;
public:
	Input(GeneralOutput* initialConnection = nullptr);
	/* Sprawdzenie czy input jest po³¹czony */
	bool IsConnected(void) const;
	/* Zwraca stan na podstawie po³¹czengo outputu */
	GeneralOutput::State_t GetState(void) const;
	/* Modyfikuje element connection */
	void Connect(GeneralOutput* connection);
};

