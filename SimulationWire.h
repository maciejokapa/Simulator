#pragma once

#include "Pin.h"
#include "SimulationPin.h"

class SimulationWire : public SimulationPin
{
public:
	SimulationWire(sf::Shape* shape);

	void Rotate(float angle) const;
	void Update(Pin::State_t state) const;

	void Transform(const sf::Vector2f& position) const;
	void OnClick(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const;
};

