#include "Clickable.h"

#include <stdio.h>

const float Clickable::baseSize = 60.0f;
const float Clickable::pinSize = 15.0f;
const uint8_t Clickable::baseShapeIdx = 0u;

Clickable::Clickable(uint8_t shapesNum) : shapes(shapesNum)
{}

bool Clickable::IsClicked(sf::Event& event) const
{
	return this->shapes[Clickable::baseShapeIdx]->getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y);
}

void Clickable::Draw(sf::RenderWindow& window) const
{
	for (const auto shape : this->shapes)
	{
		window.draw(*shape);
	}
}