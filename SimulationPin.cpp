#include "SimulationPin.h"

#include <SFML/Graphics/CircleShape.hpp>

#include <stdio.h>
SimulationPin::SimulationPin(sf::Shape* shape) : Clickable(shape)
{}	

void SimulationPin::Init(float radius, float parentNodeSize, int8_t parentPinsLen, uint8_t index, bool isInput)
{
	this->shape = new sf::CircleShape(radius);
	this->shape->setPosition(sf::Vector2f(isInput ? -radius : parentNodeSize - radius,
										  -radius + ((parentNodeSize / (parentPinsLen + 1)) * (index + 1))));
}

void SimulationPin::ChangeShape(sf::Shape* shape, sf::Color color)
{
	sf::Vector2f oldPosition;

	if (this->shape != nullptr)
	{
		oldPosition = this->shape->getPosition();
		delete this->shape;
	}

	this->shape = shape;
	this->shape->setPosition(oldPosition);
	this->UpdateColor(color);
}

void SimulationPin::UpdateColor(sf::Color color) const
{
	this->shape->setFillColor(color);
}

void SimulationPin::Transform(const sf::Vector2f& position) const
{
	this->shape->setPosition(this->shape->getPosition() + position);
}

void SimulationPin::Draw(sf::RenderWindow& window) const
{
	window.draw(*this->shape);
}