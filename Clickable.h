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
	const float baseSize;

	sf::Shape* shape;
	sf::Vector2f basePosition;

	static const float smallestNodeSize;
	static const float smallestPinSize;

public:
	Clickable(sf::Shape* shape, float xPos, float yPos, float size);

	bool IsClicked(sf::Event& event) const;

	virtual void Draw(sf::RenderWindow& window) const = 0;
	virtual void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const = 0;
};

