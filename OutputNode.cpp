#include "OutputNode.h"

#define OUTPUT_NODE_IN_LEN		(1u)
#define OUTPUT_NODE_OUT_LEN		(0u)
#define OUTPUT_NODE_SIZE		(2.0f * SimulationNode::smallestNodeSize)

OutputNode::OutputNode(NodeId_t nodeId, float xPos, float yPos)
	: SimulationNode(nodeId, OUTPUT_NODE_IN_LEN, OUTPUT_NODE_OUT_LEN, OUTPUT_NODE_SIZE)
{
	this->simulationInputs[0].Init(SimulationNode::smallestPinSize, OUTPUT_NODE_SIZE, OUTPUT_NODE_IN_LEN, 0u);

	this->Transform(sf::Vector2f(xPos - OUTPUT_NODE_SIZE / 2, yPos - OUTPUT_NODE_SIZE / 2));
	this->shape->setFillColor(sf::Color::Blue);

	this->UpdatePins();
}

bool OutputNode::Propagate(std::list<NodeId_t>& toEvaluate)
{
	(void)toEvaluate;

	this->UpdatePins();

	return true;
}

void OutputNode::OnClick(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const
{
	(void)SimulationNode::CommonRequest(event, clickInfo);
}
