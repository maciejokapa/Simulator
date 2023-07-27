#pragma once

#include "cfg.h"

void ConnAddNew(NodeId_t outputNodeId, uint8_t outputPinId, NodeId_t inputNodeId, uint8_t inputPinId);
void ConnDelete(NodeId_t inputNodeId, uint8_t inputPinId);
bool ConnFindOutput(NodeId_t inputNodeId, uint8_t inputPinId, NodeId_t* outputNodeId, uint8_t* outputPinId);
bool ConnFindOutputAndPin(NodeId_t inputNodeId, uint8_t* inputPinId, NodeId_t* outputNodeId, uint8_t* outputPinId);
bool ConnFindInputAndPin(NodeId_t outputNodeId, uint8_t* outputPinId, NodeId_t* inputNodeId, uint8_t* inputPinId);