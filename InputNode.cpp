#include "InputNode.h"

#include <SFML/Graphics/RectangleShape.hpp>

#define INPUT_NODE_IN_LEN		(1u)
#define INPUT_NODE_OUT_LEN		(1u)
#define INPUT_NODE_SIZE			(2.0f * SimulationNode::smallestNodeSize)

InputNode::InputNode(NodeId_t nodeId, float xPos, float yPos)
	: SimulationNode(nodeId, INPUT_NODE_IN_LEN, INPUT_NODE_OUT_LEN, INPUT_NODE_SIZE)
{
	this->simulationInputs[0].Init(SimulationNode::smallestPinSize, INPUT_NODE_SIZE, INPUT_NODE_IN_LEN, 0u);
	this->simulationInputs[0].ChangeShape(new sf::RectangleShape(sf::Vector2f(SimulationNode::smallestPinSize * 2, SimulationNode::smallestPinSize * 2)), sf::Color::Yellow);
	
	this->simulationOutputs[0].Init(SimulationNode::smallestPinSize, INPUT_NODE_SIZE, INPUT_NODE_OUT_LEN, 0u, false);

	this->Transform(sf::Vector2f(xPos - INPUT_NODE_SIZE / 2, yPos - INPUT_NODE_SIZE / 2));
	this->shape->setFillColor(sf::Color::Blue);
	
	this->simulationOutputs[0].Propagate(Pin::State_t::LOW);
}

bool InputNode::Propagate(std::list<NodeId_t>& toEvaluate)
{
	if (this->simulationOutputs[0].GetState() == Pin::State_t::LOW)
	{
		this->simulationOutputs[0].Propagate(Pin::State_t::HIGH);
	}
	else if (this->simulationOutputs[0].GetState() == Pin::State_t::HIGH)
	{
		this->simulationOutputs[0].Propagate(Pin::State_t::LOW);
	}

	this->InputNode::UpdatePins();

	this->simulationOutputs[0].GetConnectedObjects(toEvaluate);

	return true;
}

void InputNode::UpdatePins(void)
{
	this->simulationOutputs[0].Update();
}

void InputNode::OnClick(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const
{
	if (Clickable::ClickEventType_t::DELETE != SimulationNode::CommonRequest(event, clickInfo))
	{
		(void)this->CustomToggleRequest(event, clickInfo);
	} 
}

Clickable::ClickEventType_t InputNode::CustomToggleRequest(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const
{
	if (this->simulationInputs[0].IsClicked(event))
	{
		clickInfo.type = Clickable::ClickEventType_t::TOGGLE;
		clickInfo.nodeId = this->id;
	}

	return clickInfo.type;
}