#pragma once

#include <stdint.h>
#include "Pin.h"
#include <SFML/System/Vector2.hpp>

#define NODE_ID_INVALID		(UINT16_MAX)

typedef uint16_t NodeId_t;

enum class SimulationEventType_t {
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
	bool isInput;
	uint8_t pinId;
	void* pin;

} ConnectRequest_t;

typedef struct RequestInfo_tag {
	ConnectRequest_t connectRequest;
	MoveRequest_t moveRequest;

} RequestInfo_t;

typedef struct ClickInfo_tag {
	SimulationEventType_t type;
	NodeId_t nodeId;
	RequestInfo_t requestInfo;

} ClickInfo_t;

