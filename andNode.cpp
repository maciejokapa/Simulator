#include "andNode.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include <stdio.h>

#define AND_NODE_IN_LEN		(2u)
#define AND_NODE_OUT_LEN	(1u)
#define AND_NODE_SHAPES_NUM	(AND_NODE_IN_LEN + AND_NODE_OUT_LEN + 1u)

andNode::andNode(NodeId_t nodeId, float xPos, float yPos) : SimulationNode(nodeId, AND_NODE_IN_LEN, AND_NODE_OUT_LEN, AND_NODE_SHAPES_NUM)
{
	this->shapes[Clickable::baseShapeIdx] = new sf::RectangleShape(sf::Vector2f(Clickable::baseSize, Clickable::baseSize));
	this->shapes[Clickable::baseShapeIdx]->setPosition(xPos - Clickable::baseSize / 2, yPos - Clickable::baseSize / 2);
	this->shapes[Clickable::baseShapeIdx]->setFillColor(sf::Color::Blue);

	this->shapes[1] = new sf::RectangleShape(sf::Vector2f(Clickable::pinSize, Clickable::pinSize));
	this->shapes[1]->setPosition(xPos - Clickable::baseSize / 2, yPos - Clickable::baseSize / 4 - Clickable::pinSize / 2);
	this->shapes[1]->setFillColor(sf::Color::Red);

	this->shapes[2] = new sf::RectangleShape(sf::Vector2f(Clickable::pinSize, Clickable::pinSize));
	this->shapes[2]->setPosition(xPos - Clickable::baseSize / 2, yPos + Clickable::baseSize / 4 - Clickable::pinSize / 2);
	this->shapes[2]->setFillColor(sf::Color::Red);

	this->shapes[3] = new sf::RectangleShape(sf::Vector2f(Clickable::pinSize, Clickable::pinSize));
	this->shapes[3]->setPosition(xPos + Clickable::baseSize / 2 - Clickable::pinSize, yPos - Clickable::pinSize / 2);
	this->shapes[3]->setFillColor(sf::Color::Red);
}

void andNode::Propagate(std::queue<NodeId_t>& toEvaluate)
{
	bool isStateChanged;
	std::list<NodeId_t> tempList;

	printf("andNode::Propagate\n");

	if (this->inputs[0].GetState() == Pin::State_t::HIGH)
		this->shapes[1]->setFillColor(sf::Color::Green);
	else
		this->shapes[1]->setFillColor(sf::Color::Red);
	if (this->inputs[1].GetState() == Pin::State_t::HIGH)
		this->shapes[2]->setFillColor(sf::Color::Green);
	else
		this->shapes[2]->setFillColor(sf::Color::Red);


	if (this->inputs[0].GetState() == Pin::State_t::HIGH &&
		this->inputs[1].GetState() == Pin::State_t::HIGH)
	{
		isStateChanged = this->outputs[0].UpdateState(Pin::State_t::HIGH);
		this->shapes[3]->setFillColor(sf::Color::Green);
		printf("	HIGH\n");
	}
	else
	{
		isStateChanged = this->outputs[0].UpdateState(Pin::State_t::LOW);
		this->shapes[3]->setFillColor(sf::Color::Red);
		printf("	LOW\n");
	}

	if (isStateChanged)
	{
		printf("	state changed\n");
		this->outputs[0].GetConnectedObjects(tempList);
		for (const auto& element : tempList)
		{
			toEvaluate.push(element);
		}
	}
}

void andNode::OnClick(sf::Event& event, ClickInfo_t& clickInfo)
{
	printf("andNode::OnClick\n");
}