#include "andNode.h"

#include <stdio.h>
andNode::andNode(uint16_t nodeId) : Node(nodeId, 2, 1) 
{}

void andNode::Evaluate(void)
{
	printf("andNode::Evaluate\n");
	printf("input 0: %u\n", this->inputs[0].GetState());
	printf("input 1: %u\n", this->inputs[1].GetState());
	bool isStateChanged;

	if (this->inputs[0].GetState() == GeneralOutput::State_t::HIGH &&
		this->inputs[1].GetState() == GeneralOutput::State_t::HIGH)
	{
		isStateChanged = this->outputs[0].UpdateState(GeneralOutput::State_t::HIGH);
	}
	else
	{
		isStateChanged = this->outputs[0].UpdateState(GeneralOutput::State_t::LOW);
	}

	if (isStateChanged)
	{
		// TODO includowac tu managera i zwracac GetConnectedObjects
		// a.insert(a.end(), b.begin(), b.end());
		// this->outputs[0].GetConnectedObjects();
	}
}