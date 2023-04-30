#pragma once

#include "SimulationNode.h"

class AndNode : public SimulationNode
{
public:
	AndNode(NodeId_t nodeId, float xPos, float yPos);

	void Propagate(std::queue<NodeId_t>& toEvaluate);
	void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const;
};

