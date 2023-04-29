#include "SimulationPin.h"

SimulationPin::SimulationPin(void)
	: Clickable(nullptr, 0, 0, 0)
{}	

void SimulationPin::Init(sf::Shape* shape)
{
	this->shape = shape;
}

void SimulationPin::Transform(float xPos, float yPos)
{
	this->shape->setPosition(xPos, yPos);
}

void SimulationPin::UpdateColor(sf::Color color)
{
	this->shape->setFillColor(color);
}

void SimulationPin::Draw(sf::RenderWindow& window) const
{
	window.draw(*this->shape);
}

void SimulationPin::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	// pod³¹czanie
}