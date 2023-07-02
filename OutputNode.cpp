#include "OutputNode.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <stdio.h>

#define OUTPUT_NODE_IN_LEN		(1u)
#define OUTPUT_NODE_OUT_LEN		(0u)
#define OUTPUT_NODE_SIZE		(2.0f * SimulationNode::smallestNodeSize)

OutputNode::OutputNode(NodeId_t nodeId, float xPos, float yPos)
	: SimulationNode(nodeId, OUTPUT_NODE_IN_LEN, OUTPUT_NODE_OUT_LEN, new sf::RectangleShape(sf::Vector2f(OUTPUT_NODE_SIZE, OUTPUT_NODE_SIZE)), xPos, yPos, OUTPUT_NODE_SIZE)
{
	this->simulationInputs[0].Init(SimulationNode::smallestPinSize, OUTPUT_NODE_SIZE, OUTPUT_NODE_IN_LEN, 0u);

	this->Transform(sf::Vector2f(this->basePosition.x - OUTPUT_NODE_SIZE / 2, this->basePosition.y - OUTPUT_NODE_SIZE / 2));
	this->shape->setFillColor(sf::Color::Blue);

	this->UpdatePins();
}

bool OutputNode::Propagate(std::list<NodeId_t>& toEvaluate)
{
	printf("OutputNode::Propagate\n");
	(void)toEvaluate;

	this->UpdatePins();

	return true;
}

void OutputNode::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("OutputNode::OnClick\n");
	(void)SimulationNode::CommonRequest(event, clickInfo);
}
