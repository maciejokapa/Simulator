#pragma once

#include "Output.h"
#include "SimulationPin.h"

#include <SFML/System/Vector2.hpp>

class SimulationOutput : public Output, public SimulationPin
{
public:
	SimulationOutput(void);

	void Update(void);
	bool Propagate(Pin::State_t state);
	const sf::Vector2f& GetPosition() const;
	const float GetSize() const;

	void OnClick(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const;
};

