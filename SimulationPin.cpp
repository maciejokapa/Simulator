#include "SimulationPin.h"

SimulationPin::SimulationPin(sf::Shape* shape) : Clickable(shape)
{}	

void SimulationPin::Init(sf::Shape* shape)
{
	this->shape = shape;
}

void SimulationPin::UpdateColor(sf::Color color) const
{
	this->shape->setFillColor(color);
}

void SimulationPin::Transform(const sf::Vector2f& position) const
{
	this->shape->setPosition(position);
}

void SimulationPin::Draw(sf::RenderWindow& window) const
{
	window.draw(*this->shape);
}