#include "Output.h"

#include <algorithm>

Output::Output(GeneralOutput::State_t initialState) : GeneralOutput(initialState)
{
	this->connectedObjectsId.clear();
}

Output::Output(GeneralOutput::State_t initialState, uint16_t initialObject) : GeneralOutput(initialState)
{
	this->connectedObjectsId.clear();
	this->connectedObjectsId.push_back(initialObject);
}

bool Output::UpdateState(GeneralOutput::State_t newState)
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

void Output::Connect(uint16_t newConnectedObject)
{
	if (this->connectedObjectsId.end() == 
		std::find(this->connectedObjectsId.begin(), this->connectedObjectsId.end(), newConnectedObject))
	{
		this->connectedObjectsId.push_back(newConnectedObject);
	}
}

void Output::GetConnectedObjects(std::list<uint16_t>& connectedObjectsId) const
{
	connectedObjectsId = this->connectedObjectsId;
}
