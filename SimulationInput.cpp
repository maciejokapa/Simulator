#include "SimulationInput.h"
#include <SFML/Graphics/RectangleShape.hpp>

#include <cmath>
#include <stdio.h>

SimulationInput::SimulationInput(void) : Input(), SimulationPin()
{
	this->wire = nullptr;
}

void SimulationInput::Connect(SimulationOutput* connection)
{
	const float size = connection->GetSize();
	const sf::Vector2f position = connection->GetPosition();
	const sf::Vector2f offset = this->shape->getPosition() - position;
	const float length = sqrtf(offset.x * offset.x + offset.y * offset.y);

	this->Input::Connect(connection);
	this->wire = new SimulationWire(new sf::RectangleShape(sf::Vector2f(length, size)));
	this->wire->Transform(sf::Vector2f(position.x + size / 2, position.y + size / 2));
	this->wire->Rotate(atan2f(offset.y, offset.x) * 180.0f / (atan(1.0) * 4));
}

void SimulationInput::Disonnect(void)
{
	this->Input::Disonnect();
	delete this->wire;
}

void SimulationInput::Update(void)
{
	Pin::State_t currentState = this->GetState();

	switch (currentState)
	{
		case Pin::State_t::LOW:
		{
			this->UpdateColor(sf::Color::Red);
			break;
		}

		case Pin::State_t::HIGH:
		{
			this->UpdateColor(sf::Color::Green);
			break;
		}

		case Pin::State_t::UNDEFINED:
		{
			this->UpdateColor(sf::Color::Black);
			break;
		}
	}

	if (this->IsConnected())
	{
		this->wire->Update(currentState);
	}
}

void SimulationInput::Transform(const sf::Vector2f& position) const
{
	this->SimulationPin::Transform(position);
	if (this->IsConnected())
	{
		this->wire->Transform(position);
	}
}

void SimulationInput::Draw(sf::RenderWindow& window) const
{
	this->Clickable::Draw(window);
	if (this->IsConnected())
	{
		this->wire->Draw(window);
	}
}

bool SimulationInput::IsClicked(sf::Event& event) const
{
	bool isClicked;

	isClicked = this->Clickable::IsClicked(event);
	if (this->IsConnected())
	{
		isClicked |= this->wire->IsClicked(event);
	}

	return isClicked;
}

void SimulationInput::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	clickInfo.type = SimulationEventType_t::CONNECT;
	clickInfo.requestInfo.connectRequest.isInput = true;
	clickInfo.requestInfo.connectRequest.pin = (void*)this;
}
