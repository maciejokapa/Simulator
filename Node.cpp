#include "Node.h"

#include <iostream>

Node::Node(NodeId_t nodeId, uint16_t inLen, uint16_t outLen) : id(nodeId), inputs(inLen, Input()), outputs(outLen, Output(Pin::State_t::UNDEFINED)) {};
