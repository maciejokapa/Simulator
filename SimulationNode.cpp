#include "SimulationNode.h"


SimulationNode::SimulationNode(NodeId_t nodeId, uint16_t inLen, uint16_t outLen, sf::Shape* shape, float xPos, float yPos, float size)
	: Node(nodeId, inLen, outLen), 
		Clickable(shape, xPos, yPos, size), 
		simulationInputs(inLen, SimulationPin()), 
		simulationOutputs(outLen, SimulationPin())
{}