#include "SimulationOutput.h"

#include <stdio.h>

SimulationOutput::SimulationOutput(void) : Output(), SimulationPin()
{}

void SimulationOutput::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("SimulationOutput::OnClick");
}
