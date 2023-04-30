#include "SimulationInput.h"

#include <stdio.h>

SimulationInput::SimulationInput(void) : Input(), SimulationPin()
{}

void SimulationInput::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("SimulationInput::OnClick");
}