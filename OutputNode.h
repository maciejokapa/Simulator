#pragma once

#include "SimulationNode.h"

class OutputNode : public SimulationNode
{
public:
	OutputNode(NodeId_t nodeId, float xPos, float yPos);
	void Propagate(std::queue<NodeId_t>& toEvaluate);
	void OnClick(sf::Event& event, ClickInfo_t& clickInfo);
};
