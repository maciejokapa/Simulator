#pragma once


class GeneralOutput
{
public:
	enum class State_t
	{
		LOW,
		HIGH,
		HIGH_Z,
		UNDEFINED
	};

	State_t GetState(void);

	GeneralOutput(State_t state);

protected:
	/* Aktualny stan ouptutu */
	State_t currentState;
};
