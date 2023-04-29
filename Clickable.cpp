#include "Clickable.h"

#include <stdio.h>

const float Clickable::smallestNodeSize = 30.0f;
const float Clickable::smallestPinSize = smallestNodeSize / 3.0f;


Clickable::Clickable(sf::Shape* shape, float xPos, float yPos, float size) : shape(shape), basePosition(xPos, yPos), baseSize(size)
{}

bool Clickable::IsClicked(sf::Event& event) const
{
	return this->shape->getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y);
}
