#include "AndNode.h"

#include <stdio.h>

#define AND_NODE_IN_LEN		(2u)
#define AND_NODE_OUT_LEN	(1u)

#define AND_NODE_SIZE		(2.0f * SimulationNode::smallestNodeSize)

AndNode::AndNode(NodeId_t nodeId, float xPos, float yPos) 
	: SimulationNode(nodeId, AND_NODE_IN_LEN, AND_NODE_OUT_LEN, AND_NODE_SIZE, xPos, yPos)
{
	uint8_t index;

	index = 0u;
	for (auto& input : this->simulationInputs)
	{
		input.Init(SimulationNode::smallestPinSize, AND_NODE_SIZE,  AND_NODE_IN_LEN, index);
		index++;
	}

	index = 0u;
	for (auto& output : this->simulationOutputs)
	{
		output.Init(SimulationNode::smallestPinSize, AND_NODE_SIZE,  AND_NODE_OUT_LEN, index, false);
		index++;
	}

	this->Transform(sf::Vector2f(this->basePosition.x - AND_NODE_SIZE / 2, this->basePosition.y - AND_NODE_SIZE / 2));
	this->shape->setFillColor(sf::Color::Blue);

	this->UpdatePins();
}

bool AndNode::Propagate(std::list<NodeId_t>& toEvaluate)
{
	bool isStateChanged;

	printf("AndNode::Propagate\n");

	isStateChanged = false;

	if ((this->simulationInputs[0].GetState() != Pin::State_t::UNDEFINED) &&
		(this->simulationInputs[1].GetState() != Pin::State_t::UNDEFINED))
	{
		if (this->simulationInputs[0].GetState() == Pin::State_t::HIGH &&
			this->simulationInputs[1].GetState() == Pin::State_t::HIGH)
		{
			isStateChanged = this->simulationOutputs[0].Propagate(Pin::State_t::HIGH);
			printf("	HIGH\n");
		}
		else
		{
			isStateChanged = this->simulationOutputs[0].Propagate(Pin::State_t::LOW);
			printf("	LOW\n");
		}

		printf("	state changed\n");
	}
	else
	{
		isStateChanged = this->simulationOutputs[0].Propagate(Pin::State_t::LOW);
	}

	this->UpdatePins();
	
	this->simulationOutputs[0].GetConnectedObjects(toEvaluate);

	return isStateChanged;
}

void AndNode::OnClick(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("AndNode::OnClick\n");
	(void)SimulationNode::CommonRequest(event, clickInfo);
}
