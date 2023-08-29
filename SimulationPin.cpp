#include "SimulationPin.h"

#include <SFML/Graphics/CircleShape.hpp>

SimulationPin::SimulationPin(sf::Shape* shape) : Clickable(shape)
{}	

void SimulationPin::Init(float radius, float parentNodeSize, int8_t parentPinsLen, uint8_t index, bool isInput)
{
	this->shape = new sf::CircleShape(radius);
	this->offsetPosition = sf::Vector2f(isInput ? -radius : parentNodeSize - radius,
												  -radius + ((parentNodeSize / (parentPinsLen + 1)) * (index + 1)));
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

void SimulationPin::UpdateColor(Pin::State_t state) const
{
	switch (state)
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

void SimulationPin::Transform(const sf::Vector2f& position) const
{
	this->Clickable::Transform(this->offsetPosition + position);
}
