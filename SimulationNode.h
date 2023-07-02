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

	SimulationEventType_t CommonRequest(sf::Event& event, ClickInfo_t& clickInfo) const;

public:
	//TEMPOARORY
	//MOVE IT TO PROTECTED
	std::vector<SimulationInput> simulationInputs;
	std::vector<SimulationOutput> simulationOutputs;
	//TEMPOARORY

	SimulationNode(NodeId_t nodeId, uint16_t inLen, uint16_t outLen, sf::Shape* shape, float xPos, float yPos, float size);

	bool IsClicked(sf::Event& event) const;

	void UpdatePins(void);

	void Draw(sf::RenderWindow& window) const;
	void Transform(const sf::Vector2f& position) const;

	virtual bool Propagate(std::list<NodeId_t>&) = 0;
};

