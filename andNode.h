#pragma once

#include "Node.h"

class andNode : public Node
{
public:
	andNode(uint16_t nodeId);
	void Evaluate(void);
};

