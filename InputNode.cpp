#include "InputNode.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include <stdio.h>

#define INPUT_NODE_IN_LEN		(0u)
#define INPUT_NODE_OUT_LEN		(1u)
#define INPUT_NODE_SHAPES_NUM	(INPUT_NODE_IN_LEN + INPUT_NODE_OUT_LEN + 1u)

InputNode::InputNode(NodeId_t nodeId, float xPos, float yPos) : SimulationNode(nodeId, INPUT_NODE_IN_LEN, INPUT_NODE_OUT_LEN, INPUT_NODE_SHAPES_NUM)
{
	this->outputs[0].UpdateState(Pin::State_t::LOW);

	this->shapes[Clickable::baseShapeIdx] = new sf::RectangleShape(sf::Vector2f(Clickable::baseSize, Clickable::baseSize));
	this->shapes[Clickable::baseShapeIdx]->setPosition(xPos - Clickable::baseSize / 2, yPos - Clickable::baseSize / 2);
	this->shapes[Clickable::baseShapeIdx]->setFillColor(sf::Color::Blue);

	this->shapes[1] = new sf::RectangleShape(sf::Vector2f(Clickable::pinSize, Clickable::pinSize));
	this->shapes[1]->setPosition(xPos + Clickable::baseSize / 2 - Clickable::pinSize, yPos - Clickable::pinSize / 2);
	this->shapes[1]->setFillColor(sf::Color::Red);
}

void InputNode::Propagate(std::queue<NodeId_t>& toEvaluate)
{
	std::list<uint16_t> tempList;

	printf("InputNode::Propagate\n");

	if (this->outputs[0].GetState() == Pin::State_t::LOW)
	{
		this->outputs[0].UpdateState(Pin::State_t::HIGH);
		this->shapes[1]->setFillColor(sf::Color::Green);
		printf("	LOW->HIGH\n");
	}
	else if (this->outputs[0].GetState() == Pin::State_t::HIGH)
	{
		this->outputs[0].UpdateState(Pin::State_t::LOW);
		this->shapes[1]->setFillColor(sf::Color::Red);
		printf("	HIGH->LOW\n");
	}

	this->outputs[0].GetConnectedObjects(tempList);
	for (const auto& e : tempList)
	{
		toEvaluate.push(e);
	}
}

void InputNode::OnClick(sf::Event& event, ClickInfo_t& clickInfo)
{
	printf("InputNode::OnClick\n");

	clickInfo.type = ClickType_t::TOGGLE;
	clickInfo.nodeId = this->id;
}