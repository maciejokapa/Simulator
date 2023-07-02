#include "SimulationWire.h"

#include <stdio.h>

SimulationWire::SimulationWire(sf::Shape* shape) : SimulationPin(shape)
{}

void SimulationWire::Rotate(float angle) const
{
	this->shape->setRotation(angle);
}

void SimulationWire::Update(Pin::State_t state) const
{
	switch (state)
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

void SimulationWire::Transform(const sf::Vector2f& position) const
{
	this->Clickable::Transform(position);
}

void SimulationWire::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("SimulationWire::OnClick");
}
