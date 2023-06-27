#pragma once

#include "Clickable.h"

class SimulationPin : public Clickable
{
protected:
	void UpdateColor(sf::Color color) const;

public:
	SimulationPin(sf::Shape* shape = nullptr);

	void Init(float radius, float parentNodeSize, int8_t parentPinsLen, uint8_t index, bool isInput = true);
	void ChangeShape(sf::Shape* shape, sf::Color color);

	void Transform(const sf::Vector2f& position) const;
};

