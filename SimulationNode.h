#pragma once

#include "Clickable.h"
#include "SimulationInput.h"
#include "SimulationOutput.h"
#include "cfg.h"

#include <queue>

class SimulationNode : public Clickable
{
protected:
	const NodeId_t id;

	const float baseSize;
	sf::Vector2f basePosition;

	static const float smallestNodeSize;
	static const float smallestPinSize;

	std::vector<SimulationInput> simulationInputs;
	std::vector<SimulationOutput> simulationOutputs;

	SimulationEventType_t CommonRequest(sf::Event& event, ClickInfo_t& clickInfo) const;

public:

	SimulationNode(NodeId_t nodeId, uint16_t inLen, uint16_t outLen, float nodeSize, float xPos, float yPos);

	bool IsClicked(sf::Event& event) const;

	void UpdatePins(void);

	void Connect(uint8_t internalPinId, ClickInfo_t& connectionClickInfo);
	void Disconnect(uint8_t pinId, bool isInput, NodeId_t nodeId);

	void Draw(sf::RenderWindow& window) const;
	void Transform(const sf::Vector2f& position) const;

	virtual bool Propagate(std::list<NodeId_t>& toEvaluate) = 0;
};

