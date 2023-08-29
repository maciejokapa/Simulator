#include "Clickable.h"

Clickable::Clickable(sf::Shape* shape) : shape(shape)
{}

bool Clickable::IsClicked(sf::Event& event) const
{
	return this->shape->getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y);
}

void Clickable::Transform(const sf::Vector2f& position) const
{
	this->shape->setPosition(position);
}

void Clickable::Draw(sf::RenderWindow& window) const
{
	window.draw(*this->shape);
}