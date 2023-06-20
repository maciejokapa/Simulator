#pragma once

#include "SimulationNode.h"

class InputNode : public SimulationNode
{
private:

public:
	InputNode(NodeId_t nodeId, float xPos, float yPos);

	/* Name shadowed for similiarity with other nodes */
	void UpdatePins(void);

	void Propagate(std::queue<NodeId_t>& toEvaluate);
	void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const;
};

