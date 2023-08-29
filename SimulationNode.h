#pragma once

#include "cfg.h"
#include "Clickable.h"
#include "SimulationInput.h"
#include "SimulationOutput.h"

#include <queue>

class SimulationNode : public Clickable
{
protected:
	const NodeId_t id;

	std::vector<SimulationInput> simulationInputs;
	std::vector<SimulationOutput> simulationOutputs;

	Clickable::ClickEventType_t CommonRequest(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const;

public:
	static const float smallestNodeSize;
	static const float smallestPinSize;

	SimulationNode(NodeId_t nodeId, uint16_t inLen, uint16_t outLen, float nodeSize);

	bool IsClicked(sf::Event& event) const;

	void UpdatePins(void);

	void Connect(uint8_t internalPinId, Clickable::ClickInfo_t& connectionClickInfo);
	void Disconnect(uint8_t pinId, bool isInput, NodeId_t nodeId);

	void Draw(sf::RenderWindow& window) const;
	void Transform(const sf::Vector2f& position) const;

	virtual bool Propagate(std::list<NodeId_t>& toEvaluate) = 0;
};

