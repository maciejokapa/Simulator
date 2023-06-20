#pragma once

#include "Output.h"
#include "SimulationPin.h"

class SimulationOutput : public Output, public SimulationPin
{
public:
	SimulationOutput(void);

	void Update(void);
	bool Propagate(Pin::State_t state);

	void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const;
};

