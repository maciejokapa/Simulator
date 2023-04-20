#include "SimulationNode.h"


SimulationNode::SimulationNode(NodeId_t nodeId, uint16_t inLen, uint16_t outLen, uint8_t shapesNum)
	: Node(nodeId, inLen, outLen), Clickable(shapesNum)
{}