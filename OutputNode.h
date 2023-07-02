#pragma once

#include "SimulationNode.h"

class OutputNode : public SimulationNode
{
public:
	OutputNode(NodeId_t nodeId, float xPos, float yPos);

	bool Propagate(std::list<NodeId_t>&);
	void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const;
};
