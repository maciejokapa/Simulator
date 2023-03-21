#pragma once

#include "Node.h"

class InputNode : public Node
{
public:
	InputNode(uint16_t nodeId);
	void Evaluate(void);
};

