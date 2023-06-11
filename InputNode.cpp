#include "InputNode.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <stdio.h>

#define INPUT_NODE_IN_LEN		(1u)
#define INPUT_NODE_OUT_LEN		(1u)
#define INPUT_NODE_SIZE			(2.0f * SimulationNode::smallestNodeSize)

InputNode::InputNode(NodeId_t nodeId, float xPos, float yPos)
	: SimulationNode(nodeId, INPUT_NODE_IN_LEN, INPUT_NODE_OUT_LEN, new sf::RectangleShape(sf::Vector2f(INPUT_NODE_SIZE, INPUT_NODE_SIZE)), xPos, yPos, INPUT_NODE_SIZE)
{
	this->shape->setPosition(this->basePosition.x - INPUT_NODE_SIZE/2, this->basePosition.y - INPUT_NODE_SIZE / 2);
	this->shape->setFillColor(sf::Color::Blue);

	this->simulationInputs[0].pin.Init(new sf::RectangleShape(sf::Vector2f(SimulationNode::smallestPinSize * 2, SimulationNode::smallestPinSize * 2)));
	this->simulationInputs[0].offset.x = this->basePosition.x - INPUT_NODE_SIZE / 2;
	this->simulationInputs[0].offset.y = this->basePosition.y - SimulationNode::smallestPinSize;
	this->simulationInputs[0].pin.Transform(this->simulationInputs[0].offset);
	this->simulationInputs[0].pin.UpdateColor(sf::Color::Yellow);

	this->simulationOutputs[0].pin.Init(new sf::CircleShape(SimulationNode::smallestPinSize));
	this->simulationOutputs[0].offset.x = this->basePosition.x + INPUT_NODE_SIZE / 2 - SimulationNode::smallestPinSize * 2;
	this->simulationOutputs[0].offset.y = this->basePosition.y - SimulationNode::smallestPinSize;
	this->simulationOutputs[0].pin.Transform(this->simulationOutputs[0].offset);
	this->simulationOutputs[0].pin.UpdateState(Pin::State_t::LOW);
	this->simulationOutputs[0].pin.UpdateColor(sf::Color::Red);
}

void InputNode::Propagate(std::queue<NodeId_t>& toEvaluate)
{
	std::list<uint16_t> tempList;

	printf("InputNode::Propagate\n");

	if (this->simulationOutputs[0].pin.GetState() == Pin::State_t::LOW)
	{
		this->simulationOutputs[0].pin.UpdateState(Pin::State_t::HIGH);
		this->simulationOutputs[0].pin.UpdateColor(sf::Color::Green);
		printf("	LOW->HIGH\n");
	}
	else if (this->simulationOutputs[0].pin.GetState() == Pin::State_t::HIGH)
	{
		this->simulationOutputs[0].pin.UpdateState(Pin::State_t::LOW);
		this->simulationOutputs[0].pin.UpdateColor(sf::Color::Red);
		printf("	HIGH->LOW\n");
	}

	this->simulationOutputs[0].pin.GetConnectedObjects(tempList);
	for (const auto& e : tempList)
	{
		toEvaluate.push(e);
	}
}

void InputNode::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("InputNode::OnClick\n");
	if (!SimulationNode::CommonDeleteRequest(event, clickInfo))
	{
		if (this->simulationInputs[0].pin.IsClicked(event))
		{
			clickInfo.type = SimulationEventType_t::TOGGLE;
			clickInfo.nodeId = this->id;
			printf("CSTOM TOGGLE REQUEST\n");
		}
		else
		{
			(void)SimulationNode::CommonConnectRequest(event, clickInfo);
		}
	} 
}
