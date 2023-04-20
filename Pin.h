#pragma once


class Pin
{
public:
	enum class State_t
	{
		LOW,
		HIGH,
		UNDEFINED
	};

	State_t GetState(void) const;

	Pin(State_t state);

protected:
	/* Aktualny stan ouptutu */
	State_t currentState;
};