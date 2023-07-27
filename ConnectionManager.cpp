#include "ConnectionManager.h"
#include <map>

#include <stdio.h>

#define ENCODE_KEY(_NODE_ID_, _PIN_ID_)		((uint32_t)((((uint32_t)(_PIN_ID_)) << 16u) | _NODE_ID_))

#define DECODE_PIN(_KEY_)					((_KEY_) >> 16u)
#define DECODE_NODE(_KEY_)					((_KEY_) & 0xFFFF)

static std::map<uint32_t, uint32_t> connections;

void ConnAddNew(NodeId_t outputNodeId, uint8_t outputPinId, NodeId_t inputNodeId, uint8_t inputPinId)
{
	connections[ENCODE_KEY(inputNodeId, inputPinId)] = ENCODE_KEY(outputNodeId, outputPinId);
}

void ConnDelete(NodeId_t inputNodeId, uint8_t inputPinId)
{
	uint32_t key;

	key = ENCODE_KEY(inputNodeId, inputPinId);

	if (connections.find(key) != connections.end())
	{
		connections.erase(key);
	}
}

bool ConnFindOutput(NodeId_t inputNodeId, uint8_t inputPinId, NodeId_t* outputNodeId, uint8_t* outputPinId)
{
	uint32_t key;
	uint32_t value;
	bool result;

	key = ENCODE_KEY(inputNodeId, inputPinId);
	result = false;

	if (connections.find(key) != connections.end())
	{
		value = connections[key];

		*outputNodeId = DECODE_NODE(value);
		*outputPinId = DECODE_PIN(value);

		result = true;
	}

	return result;
}

bool ConnFindOutputAndPin(NodeId_t inputNodeId, uint8_t* inputPinId, NodeId_t* outputNodeId, uint8_t* outputPinId)
{
	uint32_t value;
	uint32_t key;
	bool result;

	result = false;

	for (const auto& element : connections)
	{
		key = element.first;
		value = element.second;

		if (DECODE_NODE(key) == inputNodeId)
		{
			*inputPinId = DECODE_PIN(key);

			*outputNodeId = DECODE_NODE(value);
			*outputPinId = DECODE_PIN(value);

			result = true;
			break;
		}
	}

	return result;
}

bool ConnFindInputAndPin(NodeId_t outputNodeId, uint8_t* outputPinId, NodeId_t* inputNodeId, uint8_t* inputPinId)
{
	uint32_t value;
	uint32_t key;
	bool result;

	result = false;

	for (const auto& element : connections)
	{
		key = element.first;
		value = element.second;

		if (DECODE_NODE(value) == outputNodeId)
		{
			*inputNodeId = DECODE_NODE(key);
			*inputPinId = DECODE_PIN(key);

			*outputPinId = DECODE_PIN(value);

			result = true;
			break;
		}
	}

	return result;
}