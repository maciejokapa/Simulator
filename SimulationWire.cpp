#include "SimulationWire.h"

SimulationWire::SimulationWire(sf::Shape* shape) : SimulationPin(shape)
{}

void SimulationWire::Rotate(float angle) const
{
	this->shape->setRotation(angle);
}

void SimulationWire::Update(Pin::State_t state) const
{
	this->UpdateColor(state);
}

void SimulationWire::Transform(const sf::Vector2f& position) const
{
	this->Clickable::Transform(position);
}

void SimulationWire::OnClick(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const
{
	(void)event;
	(void)clickInfo;
}
