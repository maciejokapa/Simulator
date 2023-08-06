#pragma once

#include "SimulationPin.h"
#include "Pin.h"

class SimulationWire : public SimulationPin
{
public:
	SimulationWire(sf::Shape* shape);

	void GetSize(float angle) const;
	void Rotate(float angle) const;
	void Update(Pin::State_t state) const;

	void Transform(const sf::Vector2f& position) const;
	void OnClick(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const;
};

