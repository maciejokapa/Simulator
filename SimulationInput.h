#pragma once

#include "Input.h"
#include "SimulationPin.h"

class SimulationInput : public Input, public SimulationPin
{
public:
	SimulationInput(void);

	void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const;
};

