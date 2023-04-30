#include "OutputNode.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <stdio.h>

#define OUTPUT_NODE_IN_LEN		(1u)
#define OUTPUT_NODE_OUT_LEN		(0u)
#define OUTPUT_NODE_SIZE		(1.0f * SimulationNode::smallestNodeSize)

OutputNode::OutputNode(NodeId_t nodeId, float xPos, float yPos)
	: SimulationNode(nodeId, OUTPUT_NODE_IN_LEN, OUTPUT_NODE_OUT_LEN, new sf::RectangleShape(sf::Vector2f(OUTPUT_NODE_SIZE, OUTPUT_NODE_SIZE)), xPos, yPos, OUTPUT_NODE_SIZE)
{
	this->shape->setPosition(this->basePosition.x - OUTPUT_NODE_SIZE / 2, this->basePosition.y - OUTPUT_NODE_SIZE / 2);
	this->shape->setFillColor(sf::Color::Blue);

	this->simulationInputs[0].pin.Init(new sf::CircleShape(SimulationNode::smallestPinSize));
	this->simulationInputs[0].offset.x = this->basePosition.x - OUTPUT_NODE_SIZE / 2;
	this->simulationInputs[0].offset.y = this->basePosition.y - SimulationNode::smallestPinSize;
	this->simulationInputs[0].pin.Transform(this->simulationInputs[0].offset);
	this->simulationInputs[0].pin.UpdateColor(sf::Color::Red);
}

void OutputNode::Propagate(std::queue<NodeId_t>& toEvaluate)
{
	printf("OutputNode::Propagate\n");
	(void)toEvaluate;

	if (this->simulationInputs[0].pin.GetState() == Pin::State_t::LOW)
	{
		this->simulationInputs[0].pin.UpdateColor(sf::Color::Red);
		printf("	LOW\n");
	}
	else if (this->simulationInputs[0].pin.GetState() == Pin::State_t::HIGH)
	{
		this->simulationInputs[0].pin.UpdateColor(sf::Color::Green);
		printf("	HIGH\n");
	}
}

void OutputNode::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("OutputNode::OnClick\n");
}
