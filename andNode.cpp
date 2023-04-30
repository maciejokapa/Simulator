#include "AndNode.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <stdio.h>

#define AND_NODE_IN_LEN		(2u)
#define AND_NODE_OUT_LEN	(1u)

#define AND_NODE_SIZE		(2.0f * SimulationNode::smallestNodeSize)

AndNode::AndNode(NodeId_t nodeId, float xPos, float yPos) 
	: SimulationNode(nodeId, AND_NODE_IN_LEN, AND_NODE_OUT_LEN, new sf::RectangleShape(sf::Vector2f(AND_NODE_SIZE, AND_NODE_SIZE)), xPos, yPos, AND_NODE_SIZE)
{
	this->shape->setPosition(this->basePosition.x - AND_NODE_SIZE / 2, this->basePosition.y - AND_NODE_SIZE / 2);
	this->shape->setFillColor(sf::Color::Blue);

	this->simulationInputs[0].pin.Init(new sf::CircleShape(SimulationNode::smallestPinSize));
	this->simulationInputs[0].offset.x = this->basePosition.x - AND_NODE_SIZE / 2;
	this->simulationInputs[0].offset.y = this->basePosition.y - AND_NODE_SIZE / 2 + SimulationNode::smallestPinSize / 2;
	this->simulationInputs[0].pin.Transform(this->simulationInputs[0].offset);
	this->simulationInputs[0].pin.UpdateColor(sf::Color::Red);

	this->simulationInputs[1].pin.Init(new sf::CircleShape(SimulationNode::smallestPinSize));
	this->simulationInputs[1].offset.x = this->basePosition.x - AND_NODE_SIZE / 2;
	this->simulationInputs[1].offset.y = this->basePosition.y - AND_NODE_SIZE / 2 + SimulationNode::smallestPinSize / 2 + SimulationNode::smallestNodeSize;
	this->simulationInputs[1].pin.Transform(this->simulationInputs[1].offset);
	this->simulationInputs[1].pin.UpdateColor(sf::Color::Red);

	this->simulationOutputs[0].pin.Init(new sf::CircleShape(SimulationNode::smallestPinSize));
	this->simulationOutputs[0].offset.x = this->basePosition.x + AND_NODE_SIZE / 2 - SimulationNode::smallestPinSize * 2;
	this->simulationOutputs[0].offset.y = this->basePosition.y - SimulationNode::smallestPinSize;
	this->simulationOutputs[0].pin.Transform(this->simulationOutputs[0].offset);
	this->simulationOutputs[0].pin.UpdateColor(sf::Color::Red);
}

void AndNode::Propagate(std::queue<NodeId_t>& toEvaluate)
{
	bool isStateChanged;
	std::list<NodeId_t> tempList;

	printf("AndNode::Propagate\n");

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
	if (this->simulationInputs[1].pin.GetState() == Pin::State_t::LOW)
	{
		this->simulationInputs[1].pin.UpdateColor(sf::Color::Red);
		printf("	LOW\n");
	}
	else if (this->simulationInputs[1].pin.GetState() == Pin::State_t::HIGH)
	{
		this->simulationInputs[1].pin.UpdateColor(sf::Color::Green);
		printf("	HIGH\n");
	}

	if (this->simulationInputs[0].pin.GetState() == Pin::State_t::HIGH &&
		this->simulationInputs[1].pin.GetState() == Pin::State_t::HIGH)
	{
		isStateChanged = this->simulationOutputs[0].pin.UpdateState(Pin::State_t::HIGH);
		this->simulationOutputs[0].pin.UpdateColor(sf::Color::Green);
		printf("	HIGH\n");
	}
	else
	{
		isStateChanged = this->simulationOutputs[0].pin.UpdateState(Pin::State_t::LOW);
		this->simulationOutputs[0].pin.UpdateColor(sf::Color::Red);
		printf("	LOW\n");
	}

	if (isStateChanged)
	{
		printf("	state changed\n");
		this->simulationOutputs[0].pin.GetConnectedObjects(tempList);
		for (const auto& element : tempList)
		{
			toEvaluate.push(element);
		}
	}
}

void AndNode::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("AndNode::OnClick\n");
}
