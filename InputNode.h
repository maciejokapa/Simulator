#pragma once

#include "SimulationNode.h"

class InputNode : public SimulationNode
{
public:
	InputNode(NodeId_t nodeId, float xPos, float yPos);
	void Propagate(std::queue<NodeId_t>& toEvaluate);
	void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const;
	void Draw(sf::RenderWindow& window) const;
};

