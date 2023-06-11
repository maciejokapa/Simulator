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
