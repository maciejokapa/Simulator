#pragma once

#include "Clickable.h"

class SimulationPin : public Clickable
{
public:
	SimulationPin(void);

	void Init(sf::Shape* shape);
	void Transform(float xPos, float yPos);
	void UpdateColor(sf::Color color);

	void Draw(sf::RenderWindow& window) const;
	void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const;
};

