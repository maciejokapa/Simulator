#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>

#include "cfg.h"

class Clickable
{
protected:
	sf::Shape* shape;

public:
	Clickable(sf::Shape* shape);

	bool IsClicked(sf::Event& event) const;

	virtual void Draw(sf::RenderWindow& window) const = 0;
	virtual void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const = 0;
	virtual void Transform(const sf::Vector2f& position) const = 0;
};

