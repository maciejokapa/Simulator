#pragma once

#include "cfg.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Event.hpp>

class Clickable
{
protected:
	sf::Shape* shape;		// TODOPTR

public:
	enum class ClickEventType_t {
		NONE,
		TOGGLE,
		CONNECT,
		DISCONNECT,
		MOVE,
		DELETE

	};

	typedef struct MoveRequest_tag {
		sf::Vector2f orgPosition;
		sf::Vector2f offset;

	} MoveRequest_t;

	typedef struct ConnectRequest_tag {
		void* pin;
		uint8_t pinId;
		bool isInput;

	} ConnectRequest_t;

	typedef struct RequestInfo_tag {
		ConnectRequest_t connectRequest;
		MoveRequest_t moveRequest;

	} RequestInfo_t;

	typedef struct ClickInfo_tag {
		ClickEventType_t type;
		NodeId_t nodeId;
		RequestInfo_t requestInfo;

	} ClickInfo_t;

	Clickable(sf::Shape* shape);

	bool IsClicked(sf::Event& event) const;
	void Draw(sf::RenderWindow& window) const;
	void Transform(const sf::Vector2f& position) const;

	virtual void OnClick(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const = 0;
};
