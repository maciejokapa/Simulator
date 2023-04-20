#pragma once

#include <vector>
#include <queue>

#include "cfg.h"
#include "Input.h"
#include "Output.h"

class Node
{
//protected:
public:
	std::vector<Input> inputs;
	std::vector<Output> outputs;

public:

	Node(NodeId_t nodeId, uint16_t inLen, uint16_t outLen);
	/* Czyta inputy. Analizuje. Ustawia outputy. Wywo³ywane przez managera jeœli dosta³ ten obiekt w notyfikacji */
	virtual void Propagate(std::queue<uint16_t>& toEvaluate) = 0;

	const NodeId_t id;
};

