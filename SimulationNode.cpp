#include "SimulationNode.h"

const float SimulationNode::smallestNodeSize = 30.0f;
const float SimulationNode::smallestPinSize = smallestNodeSize / 3.0f;

SimulationNode::SimulationNode(NodeId_t nodeId, uint16_t inLen, uint16_t outLen, sf::Shape* shape, float xPos, float yPos, float size)
	:	Clickable(shape),
		id(nodeId),
		basePosition(xPos, yPos), 
		baseSize(size), 
		simulationInputs(inLen, SimulationNode::PinInfo_t<SimulationInput>(SimulationInput(), sf::Vector2f(0, 0))),
		simulationOutputs(outLen, SimulationNode::PinInfo_t<SimulationOutput>(SimulationOutput(), sf::Vector2f(0, 0)))
{}

void SimulationNode::Draw(sf::RenderWindow& window) const
{
	window.draw(*this->shape);
	for (const auto& input : this->simulationInputs)
	{
		input.pin.Draw(window);
	}
	for (const auto& output : this->simulationOutputs)
	{
		output.pin.Draw(window);
	}
}

void SimulationNode::Transform(const sf::Vector2f& position) const
{
	this->shape->setPosition(position);
	for (const auto& input : this->simulationInputs)
	{
		input.pin.Transform(position + input.offset);
	}
	for (const auto& output : this->simulationOutputs)
	{
		output.pin.Transform(position + output.offset);
	}
}