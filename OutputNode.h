#pragma once

#include "SimulationNode.h"

class OutputNode : public SimulationNode
{
public:
	OutputNode(NodeId_t nodeId, float xPos, float yPos);

	bool Propagate(std::list<NodeId_t>& toEvaluate);
	void OnClick(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const;
};
