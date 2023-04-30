#include "Clickable.h"

#include <stdio.h>

Clickable::Clickable(sf::Shape* shape) : shape(shape)
{}

bool Clickable::IsClicked(sf::Event& event) const
{
	return this->shape->getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y);
}
