#include "Input.h"

Input::Input(GeneralOutput* initialConnection)
{
	this->connection = initialConnection;
}

bool Input::IsConnected(void) const
{
	return (nullptr != this->connection);
}

GeneralOutput::State_t Input::GetState(void) const
{
	GeneralOutput::State_t state;

	state = GeneralOutput::State_t::UNDEFINED;

	if (this->IsConnected())
	{
		state = this->connection->GetState();
	}

	return state;
}

void Input::Connect(GeneralOutput* connection)
{
	this->connection = connection;
}