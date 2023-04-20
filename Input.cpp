#include "Input.h"

Input::Input(Pin* initialConnection)
{
	this->connection = initialConnection;
}

bool Input::IsConnected(void) const
{
	return (nullptr != this->connection);
}

Pin::State_t Input::GetState(void) const
{
	Pin::State_t state;

	state = Pin::State_t::UNDEFINED;

	if (this->IsConnected())
	{
		state = this->connection->GetState();
	}

	return state;
}

void Input::Connect(Pin* connection)
{
	this->connection = connection;
}

void Input::Disonnect(Pin* connection)
{
	if (connection == this->connection)
	{
		this->connection = nullptr;
	}
}