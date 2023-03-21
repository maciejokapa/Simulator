#include "OutputNode.h"

#include <stdio.h>
OutputNode::OutputNode(uint16_t nodeId) : Node(nodeId, 1, 0)
{}

void OutputNode::Evaluate(void)
{
	if (this->inputs[0].GetState() == GeneralOutput::State_t::LOW)
	{
		printf("OutputNode::Evaluate state LOW\n");
	}
	else if (this->inputs[0].GetState() == GeneralOutput::State_t::HIGH)
	{
		printf("OutputNode::Evaluate state HIGH\n");
	}
}