#include "SimulationOutput.h"

#include <stdio.h>

SimulationOutput::SimulationOutput(void) : Output(), SimulationPin()
{}

void SimulationOutput::Update(void)
{
	switch (this->GetState())
	{
		case Pin::State_t::LOW:
		{
			this->UpdateColor(sf::Color::Red);
			break;
		}

		case Pin::State_t::HIGH:
		{
			this->UpdateColor(sf::Color::Green);
			break;
		}

		case Pin::State_t::UNDEFINED:
		{
			this->UpdateColor(sf::Color::Black);
			break;
		}
	}
}

bool SimulationOutput::Propagate(Pin::State_t state)
{
	bool isStateChanged;

	switch (state)
	{
		case Pin::State_t::LOW:
		{
			this->UpdateColor(sf::Color::Red);
			isStateChanged = this->UpdateState(Pin::State_t::LOW);
			break;
		}

		case Pin::State_t::HIGH:
		{
			this->UpdateColor(sf::Color::Green);
			isStateChanged = this->UpdateState(Pin::State_t::HIGH);
			break;
		}

		case Pin::State_t::UNDEFINED:
		{
			this->UpdateColor(sf::Color::Black);
			isStateChanged = this->UpdateState(Pin::State_t::UNDEFINED);
			break;
		}
	}

	return isStateChanged;
}

void SimulationOutput::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("SimulationOutput::OnClick");
}
