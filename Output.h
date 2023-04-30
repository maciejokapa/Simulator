#pragma once

#include <list>
#include <functional>

#include "cfg.h"
#include "Pin.h"


class Output : public Pin
{
public:

	Output(State_t initialState = Pin::State_t::LOW);
	Output(State_t initialState, NodeId_t initialObject);

	/* Ustawia nowy stan i zwraca info czy si� zmieni� czy nie */
	bool UpdateState(State_t newState);

	/* Dodaje obiekt do connectedObjects */
	void Connect(NodeId_t newConnectedObjectId);
	void Disonnect(NodeId_t connectedObjectId);

	/* Zwraca connectedObjects. B�dzie to potrzebne dla managera �eby wiedzia� kogo powiadomi� je�li stan si� zmieni */
	void GetConnectedObjects(std::list<NodeId_t>& connectedObjectsId) const;

private:
	std::list<NodeId_t> connectedObjectsId;
};
