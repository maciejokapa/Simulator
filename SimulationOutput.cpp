#include "SimulationOutput.h"

#include <SFML/Graphics/CircleShape.hpp>

SimulationOutput::SimulationOutput(void) : Output(), SimulationPin()
{}

void SimulationOutput::Update(void)
{
	this->UpdateColor(this->GetState());
}

bool SimulationOutput::Propagate(Pin::State_t state)
{
	this->UpdateColor(state);

	return this->UpdateState(state);
}

const sf::Vector2f& SimulationOutput::GetPosition() const
{
	return this->shape->getPosition();
}

const float SimulationOutput::GetSize() const
{
	return ((sf::CircleShape*)this->shape)->getRadius();
}

void SimulationOutput::OnClick(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		clickInfo.type = Clickable::ClickEventType_t::CONNECT;
		clickInfo.requestInfo.connectRequest.isInput = false;
		clickInfo.requestInfo.connectRequest.pin = (void*)this;
	}
}
