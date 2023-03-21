#include "Node.h"

#include <iostream>

Node::Node(uint16_t nodeId, uint16_t inLen, uint16_t outLen) : id(nodeId), inputs(inLen, Input()), outputs(outLen, Output(GeneralOutput::State_t::UNDEFINED)) {};
