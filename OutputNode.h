#pragma once

#include "Node.h"

class OutputNode : public Node
{
public:
	OutputNode(uint16_t nodeId);
	void Evaluate(void);
};
