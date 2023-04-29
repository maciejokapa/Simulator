#include "andNode.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <stdio.h>

#define AND_NODE_IN_LEN		(2u)
#define AND_NODE_OUT_LEN	(1u)

#define AND_NODE_SIZE		(2.0f * Clickable::smallestNodeSize)

andNode::andNode(NodeId_t nodeId, float xPos, float yPos) 
	: SimulationNode(nodeId, AND_NODE_IN_LEN, AND_NODE_OUT_LEN, new sf::RectangleShape(sf::Vector2f(AND_NODE_SIZE, AND_NODE_SIZE)), xPos, yPos, AND_NODE_SIZE)
{
	this->shape->setPosition(this->basePosition.x - AND_NODE_SIZE / 2, this->basePosition.y - AND_NODE_SIZE / 2);
	this->shape->setFillColor(sf::Color::Blue);

	this->simulationInputs[0].Init(new sf::CircleShape(Clickable::smallestPinSize));
	this->simulationInputs[0].Transform(this->basePosition.x - AND_NODE_SIZE / 2, this->basePosition.y - AND_NODE_SIZE / 2 + Clickable::smallestPinSize / 2);
	this->simulationInputs[0].UpdateColor(sf::Color::Red);

	this->simulationInputs[1].Init(new sf::CircleShape(Clickable::smallestPinSize));
	this->simulationInputs[1].Transform(this->basePosition.x - AND_NODE_SIZE / 2, this->basePosition.y - AND_NODE_SIZE / 2 + Clickable::smallestPinSize / 2 + Clickable::smallestNodeSize);
	this->simulationInputs[1].UpdateColor(sf::Color::Red);

	this->simulationOutputs[0].Init(new sf::CircleShape(Clickable::smallestPinSize));
	this->simulationOutputs[0].Transform(this->basePosition.x + AND_NODE_SIZE / 2 - Clickable::smallestPinSize * 2, this->basePosition.y - Clickable::smallestPinSize);
	this->simulationOutputs[0].UpdateColor(sf::Color::Red);
}

void andNode::Propagate(std::queue<NodeId_t>& toEvaluate)
{
	bool isStateChanged;
	std::list<NodeId_t> tempList;

	printf("andNode::Propagate\n");

	if (this->inputs[0].GetState() == Pin::State_t::LOW)
	{
		this->simulationInputs[0].UpdateColor(sf::Color::Red);
		printf("	LOW\n");
	}
	else if (this->inputs[0].GetState() == Pin::State_t::HIGH)
	{
		this->simulationInputs[0].UpdateColor(sf::Color::Green);
		printf("	HIGH\n");
	}
	if (this->inputs[1].GetState() == Pin::State_t::LOW)
	{
		this->simulationInputs[1].UpdateColor(sf::Color::Red);
		printf("	LOW\n");
	}
	else if (this->inputs[1].GetState() == Pin::State_t::HIGH)
	{
		this->simulationInputs[1].UpdateColor(sf::Color::Green);
		printf("	HIGH\n");
	}

	if (this->inputs[0].GetState() == Pin::State_t::HIGH &&
		this->inputs[1].GetState() == Pin::State_t::HIGH)
	{
		isStateChanged = this->outputs[0].UpdateState(Pin::State_t::HIGH);
		this->simulationOutputs[0].UpdateColor(sf::Color::Green);
		printf("	HIGH\n");
	}
	else
	{
		isStateChanged = this->outputs[0].UpdateState(Pin::State_t::LOW);
		this->simulationOutputs[0].UpdateColor(sf::Color::Red);
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

void andNode::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("andNode::OnClick\n");
}

void andNode::Draw(sf::RenderWindow& window) const
{
	window.draw(*this->shape);
	for (const auto& input : this->simulationInputs)
	{
		input.Draw(window);
	}
	for (const auto& output : this->simulationOutputs)
	{
		output.Draw(window);
	}
}