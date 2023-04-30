#pragma once

#include "Clickable.h"
#include "SimulationInput.h"
#include "SimulationOutput.h"
#include "cfg.h"

#include <queue>

class SimulationNode : public Clickable
{
private:
	template<typename Pin>
	class PinInfo_t {
	public:
		Pin pin;
		sf::Vector2f offset;
		PinInfo_t(Pin pin, const sf::Vector2f& offset) : pin(pin), offset(offset) {}
	};

protected:
	const NodeId_t id;

	const float baseSize;
	sf::Vector2f basePosition;

	static const float smallestNodeSize;
	static const float smallestPinSize;

public:
	//TEMPOARORY
	//MOVE IT TO PROTECTED
	std::vector<PinInfo_t<SimulationInput>> simulationInputs;
	std::vector<PinInfo_t<SimulationOutput>> simulationOutputs;


	SimulationNode(NodeId_t nodeId, uint16_t inLen, uint16_t outLen, sf::Shape* shape, float xPos, float yPos, float size);

	void Draw(sf::RenderWindow& window) const;
	void Transform(const sf::Vector2f& position) const;

	virtual void Propagate(std::queue<NodeId_t>& toEvaluate) = 0;
};

