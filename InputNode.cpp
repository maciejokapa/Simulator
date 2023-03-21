#include "InputNode.h"

#include <stdio.h>

InputNode::InputNode(uint16_t nodeId) : Node(nodeId, 0, 1)
{
	this->outputs[0].UpdateState(GeneralOutput::State_t::LOW);
}

void InputNode::Evaluate(void)
{
	if (this->outputs[0].GetState() == GeneralOutput::State_t::LOW)
	{
		this->outputs[0].UpdateState(GeneralOutput::State_t::HIGH);
	}
	else if (this->outputs[0].GetState() == GeneralOutput::State_t::HIGH)
	{
		this->outputs[0].UpdateState(GeneralOutput::State_t::LOW);
	}
}