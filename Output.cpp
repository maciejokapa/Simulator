#include "Output.h"

#include <algorithm>

Output::Output(Pin::State_t initialState) : Pin(initialState)
{
	this->connectedObjectsId.clear();
}

Output::Output(Pin::State_t initialState, NodeId_t initialObjectId) : Pin(initialState)
{
	this->connectedObjectsId.clear();
	this->connectedObjectsId.push_back(initialObjectId);
}

bool Output::UpdateState(Pin::State_t newState)
{
	bool updateResult;

	updateResult = false;

	if (this->currentState != newState)
	{
		this->currentState = newState;
		updateResult = true;
	}

	return updateResult;
}

void Output::Connect(NodeId_t newConnectedObjectId)
{
	if (this->connectedObjectsId.end() == 
		std::find(this->connectedObjectsId.begin(), this->connectedObjectsId.end(), newConnectedObjectId))
	{
		this->connectedObjectsId.push_back(newConnectedObjectId);
	}
}

void Output::Disonnect(NodeId_t connectedObjectId)
{
	this->connectedObjectsId.remove(connectedObjectId);
}

void Output::GetConnectedObjects(std::list<NodeId_t>& connectedObjectsId) const
{
	connectedObjectsId = this->connectedObjectsId;
}
