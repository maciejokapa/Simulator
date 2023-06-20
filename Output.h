#pragma once

#include <list>
#include <functional>

#include "cfg.h"
#include "Pin.h"


class Output : public Pin
{
private:
	std::list<NodeId_t> connectedObjectsId;

protected:
	bool UpdateState(State_t newState);

public:
	Output(State_t initialState = Pin::State_t::UNDEFINED);
	Output(State_t initialState, NodeId_t initialObject);

	void Connect(NodeId_t newConnectedObjectId);
	void Disonnect(NodeId_t connectedObjectId);

	void GetConnectedObjects(std::list<NodeId_t>& connectedObjectsId) const;
};
