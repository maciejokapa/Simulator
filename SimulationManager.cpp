#include "SimulationManager.h"

#include "InputNode.h"
#include "OutputNode.h"
#include "AndNode.h"

#include <stdio.h>

SimulationManager* SimulationManager::simManager = nullptr;
uint16_t SimulationManager::counter = 1u;

SimulationManager::SimulationManager(sf::RenderWindow& gameWindow) : window(gameWindow)
{
    this->state = SimulationManagerState_t::IDLE;
    memset(&this->internalClickInfo, 0u, sizeof(ClickInfo_t));

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
    //this->nodes[1]->simulationOutputs[0].pin.Connect(4);
    //this->nodes[2]->simulationOutputs[0].pin.Connect(4);
    // node.in -> input.out
    //this->nodes[4]->simulationInputs[0].pin.Connect(&this->nodes[1]->simulationOutputs[0].pin);
    //this->nodes[4]->simulationInputs[1].pin.Connect(&this->nodes[2]->simulationOutputs[0].pin);
    // node.out -> out.in
    //this->nodes[4]->simulationOutputs[0].pin.Connect(3);
    // out.in -> node.out
    //this->nodes[3]->simulationInputs[0].pin.Connect(&this->nodes[4]->simulationOutputs[0].pin);
    /* TO DELETE */
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
    
    while (window.waitEvent(event))
    {

/*-------------------------------------------------------------------*/
/*------------------- Handle special events -------------------------*/
/*-------------------------------------------------------------------*/

        if ((event.type == sf::Event::Closed) ||
            ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
        {
            window.close();
        }


/*-------------------------------------------------------------------*/
/*--------------------- Handle mouse clicks -------------------------*/
/*-------------------------------------------------------------------*/

        memset(&clickInfo, 0u, sizeof(ClickInfo_t));
        if (sf::Event::MouseButtonPressed == event.type)
        {
            for (const auto node : this->nodes)
            {
                if (node.second->IsClicked(event))
                {
                    node.second->OnClick(event, clickInfo);
                    break;
                }
            }
        }

/*-------------------------------------------------------------------*/
/*------------------- Process simulation logic ----------------------*/
/*-------------------------------------------------------------------*/

        switch (this->state)
        {
            case SimulationManagerState_t::IDLE:
            {
                switch (clickInfo.type)
                {
                    case SimulationEventType_t::TOGGLE:
                    {
                        this->PropagateSignal(clickInfo.nodeId);
                        break;
                    }
                    case SimulationEventType_t::CONNECT:
                    {
                        memcpy(&this->internalClickInfo, &clickInfo, sizeof(ClickInfo_t));
                        this->state = SimulationManagerState_t::CONNECT;
                        break;
                    }
                    case SimulationEventType_t::MOVE:
                    {
                        memcpy(&this->internalClickInfo, &clickInfo, sizeof(ClickInfo_t));
                        this->state = SimulationManagerState_t::MOVE;
                        break;
                    }
                    case SimulationEventType_t::DELETE:
                    {
                        // delete node
                        // delete connections with connected nodes
                        // push to toEvaluate all of the nodes that were connected with theirs inputs with deleted node
                        // call PropagateSignal()
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case SimulationManagerState_t::CONNECT:
            {
                if (sf::Mouse::Button::Right == event.mouseButton.button)
                {
                    memset(&this->internalClickInfo, 0u, sizeof(clickInfo));
                    this->state = SimulationManagerState_t::IDLE;
                }
                else
                {
                    if (SimulationEventType_t::CONNECT == clickInfo.type)
                    {
                        //this->nodes[1]->simulationOutputs[0].pin.Connect(4);
                        //this->nodes[4]->simulationInputs[0].pin.Connect(&this->nodes[1]->simulationOutputs[0].pin);

                        if ((internalClickInfo.requestInfo.connectRequest.isInput && !clickInfo.requestInfo.connectRequest.isInput) ||
                            (!internalClickInfo.requestInfo.connectRequest.isInput && clickInfo.requestInfo.connectRequest.isInput))
                        {
                            if (internalClickInfo.requestInfo.connectRequest.isInput)
                            {
                                (*(SimulationInput*)internalClickInfo.requestInfo.connectRequest.pin).Connect((SimulationOutput*)clickInfo.requestInfo.connectRequest.pin);
                                (*(SimulationOutput*)clickInfo.requestInfo.connectRequest.pin).Connect(internalClickInfo.nodeId);
                                this->PropagateSignal(internalClickInfo.nodeId);
                            }
                            else
                            {
                                (*(SimulationInput*)clickInfo.requestInfo.connectRequest.pin).Connect((SimulationOutput*)internalClickInfo.requestInfo.connectRequest.pin);
                                (*(SimulationOutput*)internalClickInfo.requestInfo.connectRequest.pin).Connect(clickInfo.nodeId);
                                this->PropagateSignal(clickInfo.nodeId);
                            }

                            this->state = SimulationManagerState_t::IDLE;
                            memset(&internalClickInfo, 0u, sizeof(ClickInfo_t));
                        }
                    }
                }

                break;
            }
            case SimulationManagerState_t::MOVE:
            {
                this->nodes[internalClickInfo.nodeId]->Transform(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y));
                this->PropagateSignalSingleStep(internalClickInfo.nodeId);

                if (sf::Event::MouseButtonReleased == event.type)
                {
                    this->nodes[internalClickInfo.nodeId]->Transform(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y));

                    this->PropagateSignalSingleStep(internalClickInfo.nodeId);
                    this->state = SimulationManagerState_t::IDLE;
                    memset(&internalClickInfo, 0u, sizeof(ClickInfo_t));
                }

                break;
            }
            default:
                break;
        }

/*-------------------------------------------------------------------*/
/*------------------------ Draw -------------------------------------*/
/*-------------------------------------------------------------------*/

        this->window.clear(sf::Color(82, 78, 72));
        for (const auto node : this->nodes)
        {
            node.second->Draw(this->window);
        }
        this->window.display();

/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
    }
}

void SimulationManager::PropagateSignal(NodeId_t nodeId)
{
    std::list<NodeId_t> tempList;

    this->toEvaluate.push(nodeId);
    while (!this->toEvaluate.empty())
    {
        if (this->nodes[this->toEvaluate.front()]->Propagate(tempList))
        {
            while (!tempList.empty())
            {
                this->toEvaluate.push(tempList.front());
                tempList.pop_front();
            }
        }
        this->toEvaluate.pop();
    } 
}

void SimulationManager::PropagateSignalSingleStep(NodeId_t nodeId)
{
    std::list<NodeId_t> dummyList;
    std::list<NodeId_t> tempList;

    this->toEvaluate.push(nodeId);
    this->nodes[this->toEvaluate.front()]->Propagate(tempList);
    for (const auto& element : tempList)
    {
        this->toEvaluate.push(element);
    }

    while (!this->toEvaluate.empty())
    {
        (void)this->nodes[this->toEvaluate.front()]->Propagate(dummyList);
        this->toEvaluate.pop();
    } 
}
