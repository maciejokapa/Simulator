#pragma once

#include "Input.h"
#include "SimulationPin.h"
#include "SimulationOutput.h"
#include "SimulationWire.h"

class SimulationInput : public Input, public SimulationPin
{
private:
	SimulationWire* wire;
	SimulationOutput* connection;
	float connectionSize;

	bool IsWireClicked(sf::Event& event) const;

public:
	SimulationInput(void);

	void Connect(SimulationOutput* connection);
	void Disonnect(void);

	void UpdateWire(void);
	void Update(void);

	void Transform(const sf::Vector2f& position) const;
	void Draw(sf::RenderWindow& window) const;
	bool IsClicked(sf::Event& event) const;
	void OnClick(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const;
};

