#pragma once

#include "SimulationPin.h"

class SimulationWire : public SimulationPin
{
public:
	SimulationWire(sf::Shape* shape);

	void Rotate(float angle) const;
	void Update(Pin::State_t state) const;

	void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const;
};

