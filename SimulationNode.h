#pragma once

#include "Node.h"
#include "Clickable.h"
#include "SimulationPin.h"

class SimulationNode : public Node, public Clickable
{
protected:
	std::vector<SimulationPin> simulationInputs;
	std::vector<SimulationPin> simulationOutputs;

public:
	SimulationNode(NodeId_t nodeId, uint16_t inLen, uint16_t outLen, sf::Shape* shape, float xPos, float yPos, float size);
};

