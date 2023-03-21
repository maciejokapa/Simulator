#pragma once

#include <list>
#include <functional>

#include "GeneralOutput.h"


class Output : public GeneralOutput
{
public:

	Output(State_t initialState);
	Output(State_t initialState, uint16_t initialObject);

	/* Ustawia nowy stan i zwraca info czy si� zmieni� czy nie */
	bool UpdateState(State_t newState);

	/* Dodaje obiekt do connectedObjects */
	void Connect(uint16_t newConnectedObject);

	/* Zwraca connectedObjects. B�dzie to potrzebne dla managera �eby wiedzia� kogo powiadomi� je�li stan si� zmieni */
	void GetConnectedObjects(std::list<uint16_t>& connectedObjects) const;

private:
	std::list<uint16_t> connectedObjectsId;
};
