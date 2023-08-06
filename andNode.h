#pragma once

#include "SimulationNode.h"

class AndNode : public SimulationNode
{
public:
	AndNode(NodeId_t nodeId, float xPos, float yPos);

	bool Propagate(std::list<NodeId_t>& toEvaluate);
	void OnClick(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const;
};

