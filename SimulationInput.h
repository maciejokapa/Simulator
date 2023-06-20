#pragma once

#include "Input.h"
#include "SimulationPin.h"
#include "SimulationWire.h"

class SimulationInput : public Input, public SimulationPin
{
private:
	SimulationWire* wire;

public:
	SimulationInput(void);

	void Connect(Pin* connection);
	void Disonnect(void);

	void Update(void);

	void Draw(sf::RenderWindow& window) const;
	void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const;
};

