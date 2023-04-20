#pragma once

#include <stdint.h>

typedef uint16_t NodeId_t;

enum class ClickType_t {
	NONE,
	TOGGLE,
	CONNECT,
	MOVE,
	DELETE

};

typedef struct ClickInfo_tag{
	ClickType_t type;
	NodeId_t nodeId;

} ClickInfo_t;