#pragma once

#include "Node.h"
#include "Clickable.h"

class SimulationNode : public Node, public Clickable
{
public:
	SimulationNode(NodeId_t nodeId, uint16_t inLen, uint16_t outLen, uint8_t shapesNum);
};

