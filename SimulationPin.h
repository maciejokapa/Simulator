#pragma once

#include "Clickable.h"

class SimulationPin : public Clickable
{
public:
	SimulationPin(void);

	void Init(sf::Shape* shape);
	void UpdateColor(sf::Color color) const;

	void Draw(sf::RenderWindow& window) const;
	void Transform(const sf::Vector2f& position) const;
};

