#pragma once

#include "SimulationNode.h"

class InputNode : public SimulationNode
{
private:
	SimulationEventType_t CustomToggleRequest(sf::Event& event, ClickInfo_t& clickInfo) const;
public:
	InputNode(NodeId_t nodeId, float xPos, float yPos);

	/* Name shadowed for similiarity with other nodes */
	void UpdatePins(void);

	bool Propagate(std::list<NodeId_t>&);
	void OnClick(sf::Event& event, ClickInfo_t& clickInfo) const;
};

