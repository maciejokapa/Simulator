#include "SimulationManager.h"

#include "InputNode.h"
#include "OutputNode.h"
#include "AndNode.h"

#include <stdio.h>

SimulationManager* SimulationManager::simManager = nullptr;
uint16_t SimulationManager::counter = 1u;

SimulationManager::SimulationManager(sf::RenderWindow& gameWindow) : window(gameWindow)
{
    this->nodes[counter] = new InputNode(counter, 50, 150);
    counter++;
    this->nodes[counter] = new InputNode(counter, 50, 250);
    counter++;
    this->nodes[counter] = new OutputNode(counter, 350, 200);
    counter++;
    this->nodes[counter] = new AndNode(counter, 200, 200);
    counter++;

    /* TO DELETE */
    // input.out -> node.in
    this->nodes[1]->simulationOutputs[0].pin.Connect(4);
    this->nodes[2]->simulationOutputs[0].pin.Connect(4);
    // node.in -> input.out
    this->nodes[4]->simulationInputs[0].pin.Connect(&this->nodes[1]->simulationOutputs[0].pin);
    this->nodes[4]->simulationInputs[1].pin.Connect(&this->nodes[2]->simulationOutputs[0].pin);
    // node.out -> out.in
    this->nodes[4]->simulationOutputs[0].pin.Connect(3);
    // out.in -> node.out
    this->nodes[3]->simulationInputs[0].pin.Connect(&this->nodes[4]->simulationOutputs[0].pin);
    /* TO DELETE */

    this->window.clear();
    for (const auto node : this->nodes)
    {
        node.second->Draw(this->window);
    }
    this->window.display();
}

SimulationManager* SimulationManager::GetInstance(sf::RenderWindow& gameWindow)
{
    if (SimulationManager::simManager == nullptr) 
    {
        SimulationManager::simManager = new SimulationManager(gameWindow);
    }
    return SimulationManager::simManager;
}

void SimulationManager::Run(void)
{
    ClickInfo_t clickInfo;
    sf::Event event;

    clickInfo.type = ClickType_t::NONE;
    
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            for (const auto node : this->nodes)
            {
                printf("check node %u\n", node.first);
                if (node.second->IsClicked(event))
                {
                    printf("CICKED\n");
                    node.second->OnClick(event, clickInfo);
                    break;
                }
            }
        }

        switch (clickInfo.type)
        {
            case ClickType_t::TOGGLE:
            {
                this->toEvaluate.push(clickInfo.nodeId);
                this->PropagateSignal();
                break;
            }
            case ClickType_t::CONNECT:
            {

                break;
            }
            case ClickType_t::MOVE:
            {

                break;
            }
            case ClickType_t::DELETE:
            {

                break;
            }
            default:
                break;
        }

        this->window.clear();
        for (const auto node : this->nodes)
        {
            node.second->Draw(this->window);
        }
        this->window.display();
    }
}

void SimulationManager::PropagateSignal(void)
{
    while (!this->toEvaluate.empty())
    {
        this->nodes[this->toEvaluate.front()]->Propagate(this->toEvaluate);
        this->toEvaluate.pop();
    }
}