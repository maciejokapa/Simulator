#include "OutputNode.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include <stdio.h>

#define OUTPUT_NODE_IN_LEN		(1u)
#define OUTPUT_NODE_OUT_LEN		(0u)
#define OUTPUT_NODE_SHAPES_NUM	(OUTPUT_NODE_IN_LEN + OUTPUT_NODE_OUT_LEN + 1u)

OutputNode::OutputNode(NodeId_t nodeId, float xPos, float yPos) : SimulationNode(nodeId, OUTPUT_NODE_IN_LEN, OUTPUT_NODE_OUT_LEN, OUTPUT_NODE_SHAPES_NUM)
{
	this->shapes[Clickable::baseShapeIdx] = new sf::RectangleShape(sf::Vector2f(Clickable::baseSize, Clickable::baseSize));
	this->shapes[Clickable::baseShapeIdx]->setPosition(xPos - Clickable::baseSize / 2, yPos - Clickable::baseSize / 2);
	this->shapes[Clickable::baseShapeIdx]->setFillColor(sf::Color::Blue);

	this->shapes[1] = new sf::RectangleShape(sf::Vector2f(Clickable::pinSize, Clickable::pinSize));
	this->shapes[1]->setPosition(xPos - Clickable::baseSize / 2, yPos - Clickable::pinSize / 2);
	this->shapes[1]->setFillColor(sf::Color::Red);
}

void OutputNode::Propagate(std::queue<NodeId_t>& toEvaluate)
{
	printf("OutputNode::Propagate\n");
	(void)toEvaluate;

	if (this->inputs[0].GetState() == Pin::State_t::LOW)
	{
		this->shapes[1]->setFillColor(sf::Color::Red);
		printf("	LOW\n");
	}
	else if (this->inputs[0].GetState() == Pin::State_t::HIGH)
	{
		this->shapes[1]->setFillColor(sf::Color::Green);
		printf("	HIGH\n");
	}
}

void OutputNode::OnClick(sf::Event& event, ClickInfo_t& clickInfo)
{
	printf("OutputNode::OnClick\n");
}