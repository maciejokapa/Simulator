#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "SimulationNode.h"

#include <queue>
#include <map>

class SimulationManager
{
private:

/* SimulationManager is a singleton */
    SimulationManager(sf::RenderWindow& gameWindow);
    
    void PropagateSignal(void);

    static SimulationManager* simManager;
    static uint16_t counter;
    
    std::map<NodeId_t, SimulationNode*> nodes;
    std::queue<NodeId_t> toEvaluate;

    sf::RenderWindow& window;

public:
/* SimulationManager is a singleton */
    SimulationManager(SimulationManager& other) = delete;
    void operator=(const SimulationManager&) = delete;
    static SimulationManager* GetInstance(sf::RenderWindow& gameWindow);

    void Run(void);
};
