#include "SimulationWire.h"

#include <stdio.h>

SimulationWire::SimulationWire(sf::Shape* shape) : SimulationPin(shape)
{}

void SimulationWire::Rotate(float angle) const
{
	this->shape->setRotation(angle);
}

void SimulationWire::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("SimulationWire::OnClick");
}
