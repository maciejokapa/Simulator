#include "InputNode.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <stdio.h>

#define INPUT_NODE_IN_LEN		(0u)
#define INPUT_NODE_OUT_LEN		(1u)
#define INPUT_NODE_SIZE			(1.0f * Clickable::smallestNodeSize)

InputNode::InputNode(NodeId_t nodeId, float xPos, float yPos)
	: SimulationNode(nodeId, INPUT_NODE_IN_LEN, INPUT_NODE_OUT_LEN, new sf::RectangleShape(sf::Vector2f(INPUT_NODE_SIZE, INPUT_NODE_SIZE)), xPos, yPos, INPUT_NODE_SIZE)
{
	this->outputs[0].UpdateState(Pin::State_t::LOW);

	this->shape->setPosition(this->basePosition.x - INPUT_NODE_SIZE/2, this->basePosition.y - INPUT_NODE_SIZE / 2);
	this->shape->setFillColor(sf::Color::Blue);

	this->simulationOutputs[0].Init(new sf::CircleShape(Clickable::smallestPinSize));
	this->simulationOutputs[0].Transform(this->basePosition.x + INPUT_NODE_SIZE / 2 - Clickable::smallestPinSize * 2, this->basePosition.y - Clickable::smallestPinSize);
	this->simulationOutputs[0].UpdateColor(sf::Color::Red);
}

void InputNode::Propagate(std::queue<NodeId_t>& toEvaluate)
{
	std::list<uint16_t> tempList;

	printf("InputNode::Propagate\n");

	if (this->outputs[0].GetState() == Pin::State_t::LOW)
	{
		this->outputs[0].UpdateState(Pin::State_t::HIGH);
		this->simulationOutputs[0].UpdateColor(sf::Color::Green);
		printf("	LOW->HIGH\n");
	}
	else if (this->outputs[0].GetState() == Pin::State_t::HIGH)
	{
		this->outputs[0].UpdateState(Pin::State_t::LOW);
		this->simulationOutputs[0].UpdateColor(sf::Color::Red);
		printf("	HIGH->LOW\n");
	}

	this->outputs[0].GetConnectedObjects(tempList);
	for (const auto& e : tempList)
	{
		toEvaluate.push(e);
	}
}

void InputNode::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("InputNode::OnClick\n");

	clickInfo.type = ClickType_t::TOGGLE;
	clickInfo.nodeId = this->id;
}

void InputNode::Draw(sf::RenderWindow& window) const
{
	window.draw(*this->shape);
	this->simulationOutputs[0].Draw(window);
}