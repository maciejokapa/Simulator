#pragma once

#include <vector>
#include <list>

#include "Input.h"
#include "Output.h"

class Node
{
//protected:
public:
	std::vector<Input> inputs;
	std::vector<Output> outputs;

	const uint16_t id;

public:

	Node(uint16_t nodeId, uint16_t inLen, uint16_t outLen);
	/* Czyta inputy. Analizuje. Ustawia outputy. Wywo³ywane przez managera jeœli dosta³ ten obiekt w notyfikacji */
	virtual void Evaluate(void) = 0;
};

