#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

#include "cfg.h"

class Clickable
{
protected:
	std::vector<sf::Shape*> shapes;

	static const float baseSize;
	static const float pinSize;
	static const uint8_t baseShapeIdx;
public:
	Clickable(uint8_t shapesNum);

	bool IsClicked(sf::Event& event) const;
	void Draw(sf::RenderWindow& window) const;

	virtual void OnClick(sf::Event& event, ClickInfo_t& clickInfo) = 0;
};

