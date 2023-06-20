#include "SimulationInput.h"
#include <SFML/Graphics/RectangleShape.hpp>

#include <stdio.h>

SimulationInput::SimulationInput(void) : Input(), SimulationPin()
{
	this->wire = nullptr;
}

void SimulationInput::Connect(Pin* connection)
{
	this->Input::Connect(connection);
	this->wire = new SimulationWire(new sf::RectangleShape(sf::Vector2f(20, 20)));
}

void SimulationInput::Disonnect(void)
{
	this->Input::Disonnect();
}

void SimulationInput::Update(void)
{
	switch (this->GetState())
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
}

void SimulationInput::Draw(sf::RenderWindow& window) const
{
	this->SimulationPin::Draw(window);
	if (this->Input::IsConnected())
	{
		this->wire->Draw(window);
	}
}

void SimulationInput::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("SimulationInput::OnClick");
}
