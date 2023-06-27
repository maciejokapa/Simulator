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
	this->simulationInputs[0].Init(SimulationNode::smallestPinSize, INPUT_NODE_SIZE, INPUT_NODE_IN_LEN, 0u);
	this->simulationInputs[0].ChangeShape(new sf::RectangleShape(sf::Vector2f(SimulationNode::smallestPinSize * 2, SimulationNode::smallestPinSize * 2)), sf::Color::Yellow);
	
	this->simulationOutputs[0].Init(SimulationNode::smallestPinSize, INPUT_NODE_SIZE, INPUT_NODE_OUT_LEN, 0u, false);

	this->Transform(sf::Vector2f(this->basePosition.x - INPUT_NODE_SIZE / 2, this->basePosition.y - INPUT_NODE_SIZE / 2));
	this->shape->setFillColor(sf::Color::Blue);
	
	this->simulationOutputs[0].Propagate(Pin::State_t::LOW);
}

void InputNode::Propagate(std::queue<NodeId_t>& toEvaluate)
{
	std::list<uint16_t> tempList;

	printf("InputNode::Propagate\n");

	this->UpdatePins();		

	if (this->simulationOutputs[0].GetState() == Pin::State_t::LOW)
	{
		this->simulationOutputs[0].Propagate(Pin::State_t::HIGH);
		printf("	LOW->HIGH\n");
	}
	else if (this->simulationOutputs[0].GetState() == Pin::State_t::HIGH)
	{
		this->simulationOutputs[0].Propagate(Pin::State_t::LOW);
		printf("	HIGH->LOW\n");
	}

	this->simulationOutputs[0].GetConnectedObjects(tempList);
	for (const auto& e : tempList)
	{
		toEvaluate.push(e);
	}
}

void InputNode::UpdatePins(void)
{
	this->simulationOutputs[0].Update();
}

void InputNode::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("InputNode::OnClick\n");
	if (SimulationEventType_t::DELETE != SimulationNode::CommonDeleteRequest(event, clickInfo))
	{
		if (SimulationEventType_t::TOGGLE != this->CustomToggleRequest(event, clickInfo))
		{
			(void)SimulationNode::CommonConnectRequest(event, clickInfo);
		}
	} 
}

SimulationEventType_t InputNode::CustomToggleRequest(sf::Event& event, ClickInfo_t& clickInfo) const
{
	if (this->simulationInputs[0].IsClicked(event))
	{
		clickInfo.type = SimulationEventType_t::TOGGLE;
		clickInfo.nodeId = this->id;
	}

	return clickInfo.type;
}