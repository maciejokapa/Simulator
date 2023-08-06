#pragma once

#include "Clickable.h"
#include "Pin.h"

class SimulationPin : public Clickable
{
private:
	sf::Vector2f offsetPosition;
protected:
	void UpdateColor(sf::Color color) const;
	void UpdateColor(Pin::State_t state) const;

public:
	SimulationPin(sf::Shape* shape = nullptr);

	void Init(float radius, float parentNodeSize, int8_t parentPinsLen, uint8_t index, bool isInput = true);
	void ChangeShape(sf::Shape* shape, sf::Color color);

	void Transform(const sf::Vector2f& position) const;
};

