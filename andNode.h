#pragma once

#include "SimulationNode.h"

class AndNode : public SimulationNode
{
public:
	AndNode(NodeId_t nodeId, float xPos, float yPos);

	bool Propagate(std::list<NodeId_t>&);
	void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const;
};

