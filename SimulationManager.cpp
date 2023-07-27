#include "SimulationManager.h"

#include <SFML/Window/Event.hpp>
#include <map>

#include "ConnectionManager.h"
#include "InputNode.h"
#include "OutputNode.h"
#include "AndNode.h"

#include <stdio.h>

#define SIM_BACKGROUND_COLOR        (sf::Color(82, 78, 72))

void SimPropagateSignalSingleStep(NodeId_t nodeId);
void SimPropagateSignal(NodeId_t nodeId);
void SimInit(void);
void SimOnManagerIdle(ClickInfo_t& clickInfo, ClickInfo_t& internalClickInfo, const sf::Event event);
void SimOnManagerConnect(ClickInfo_t& clickInfo, ClickInfo_t& internalClickInfo, const sf::Event event);
void SimOnManagerDisconnect(ClickInfo_t& clickInfo);
void SimOnManagerMove(ClickInfo_t& internalClickInfo, const sf::Event event);
void SimOnManagerDelete(ClickInfo_t& clickInfo);

enum class SimulationManagerState_t {
    IDLE,
    CONNECT,
    MOVE

};

static uint16_t sim_node_counter = 1u;
static std::map<NodeId_t, SimulationNode*> sim_nodes;
static SimulationManagerState_t sim_state;

void SimInit(void)
{
    sim_state = SimulationManagerState_t::IDLE;

    sim_nodes[sim_node_counter] = new InputNode(sim_node_counter, 50, 150);
    sim_node_counter++;
    sim_nodes[sim_node_counter] = new InputNode(sim_node_counter, 50, 250);
    sim_node_counter++;
    sim_nodes[sim_node_counter] = new InputNode(sim_node_counter, 50, 350);
    sim_node_counter++;
    sim_nodes[sim_node_counter] = new InputNode(sim_node_counter, 50, 450);
    sim_node_counter++;
    sim_nodes[sim_node_counter] = new OutputNode(sim_node_counter, 350, 200);
    sim_node_counter++;
    sim_nodes[sim_node_counter] = new AndNode(sim_node_counter, 200, 200);
    sim_node_counter++;
    sim_nodes[sim_node_counter] = new AndNode(sim_node_counter, 200, 300);
    sim_node_counter++;
    sim_nodes[sim_node_counter] = new AndNode(sim_node_counter, 200, 400);
    sim_node_counter++;
    sim_nodes[sim_node_counter] = new AndNode(sim_node_counter, 200, 500);
    sim_node_counter++;
    sim_nodes[sim_node_counter] = new AndNode(sim_node_counter, 200, 600);
    sim_node_counter++;
}

void SimRun(sf::RenderWindow& window)
{
    ClickInfo_t clickInfo;
    ClickInfo_t internalClickInfo;
    sf::Event event;

    memset(&internalClickInfo, 0u, sizeof(ClickInfo_t));
    
    SimInit();

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
            for (const auto node : sim_nodes)
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

        switch (sim_state)
        {
            case SimulationManagerState_t::IDLE:
            {
                SimOnManagerIdle(clickInfo, internalClickInfo, event);
                break;
            }
            case SimulationManagerState_t::CONNECT:
            {
                SimOnManagerConnect(clickInfo, internalClickInfo, event);
                break;
            }
            case SimulationManagerState_t::MOVE:
            {
                SimOnManagerMove(internalClickInfo, event);
                break;
            }
            default:
                break;
        }

/*-------------------------------------------------------------------*/
/*------------------------ Draw -------------------------------------*/
/*-------------------------------------------------------------------*/

        window.clear(SIM_BACKGROUND_COLOR);
        for (const auto node : sim_nodes)
        {
            node.second->Draw(window);
        }
        window.display();

/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
    }
}


void SimOnManagerIdle(ClickInfo_t& clickInfo, ClickInfo_t& internalClickInfo, const sf::Event event)
{
    switch (clickInfo.type)
    {
        case SimulationEventType_t::TOGGLE:
        {
            SimPropagateSignal(clickInfo.nodeId);
            break;
        }
        case SimulationEventType_t::CONNECT:
        {
            memcpy(&internalClickInfo, &clickInfo, sizeof(ClickInfo_t));
            sim_state = SimulationManagerState_t::CONNECT;
            break;
        }
        case SimulationEventType_t::DISCONNECT:
        {
            SimOnManagerDisconnect(clickInfo);
            break;
        }
        case SimulationEventType_t::MOVE:
        {
            memcpy(&internalClickInfo, &clickInfo, sizeof(ClickInfo_t));
            internalClickInfo.requestInfo.moveRequest.offset = sf::Vector2f(internalClickInfo.requestInfo.moveRequest.orgPosition.x - (float)event.mouseButton.x, internalClickInfo.requestInfo.moveRequest.orgPosition.y - (float)event.mouseButton.y);
            sim_state = SimulationManagerState_t::MOVE;
            break;
        }
        case SimulationEventType_t::DELETE:
        {
            SimOnManagerDelete(clickInfo);
            // delete node
            // delete connections with connected sim_nodes
            // push to toEvaluate all of the sim_nodes that were connected with theirs inputs with deleted node
            // call SimPropagateSignal()
            break;
        }
        default:
            break;
    }
}

void SimOnManagerConnect(ClickInfo_t& clickInfo, ClickInfo_t& internalClickInfo, const sf::Event event)
{
    if (sf::Mouse::Button::Right == event.mouseButton.button)
    {
        memset(&internalClickInfo, 0u, sizeof(clickInfo));
        sim_state = SimulationManagerState_t::IDLE;
    }
    else
    {
        if (SimulationEventType_t::CONNECT == clickInfo.type)
        {
            if ((internalClickInfo.requestInfo.connectRequest.isInput && !clickInfo.requestInfo.connectRequest.isInput) ||
                (!internalClickInfo.requestInfo.connectRequest.isInput && clickInfo.requestInfo.connectRequest.isInput))
            {
                sim_nodes[internalClickInfo.nodeId]->Connect(internalClickInfo.requestInfo.connectRequest.pinId, clickInfo);
                sim_nodes[clickInfo.nodeId]->Connect(clickInfo.requestInfo.connectRequest.pinId, internalClickInfo);

                if (internalClickInfo.requestInfo.connectRequest.isInput)
                {
                    SimPropagateSignal(internalClickInfo.nodeId);
                    ConnAddNew(clickInfo.nodeId, clickInfo.requestInfo.connectRequest.pinId, internalClickInfo.nodeId, internalClickInfo.requestInfo.connectRequest.pinId);
                }
                else
                {
                    SimPropagateSignal(clickInfo.nodeId);
                    ConnAddNew(internalClickInfo.nodeId, internalClickInfo.requestInfo.connectRequest.pinId, clickInfo.nodeId, clickInfo.requestInfo.connectRequest.pinId);
                }

                sim_state = SimulationManagerState_t::IDLE;
                memset(&internalClickInfo, 0u, sizeof(ClickInfo_t));
            }
        }
    }
}

void SimOnManagerDisconnect(ClickInfo_t& clickInfo)
{
    NodeId_t outputNodeId;
    uint8_t outputPinId;

    if (ConnFindOutput(clickInfo.nodeId, clickInfo.requestInfo.connectRequest.pinId, &outputNodeId, &outputPinId))
    {
        ConnDelete(clickInfo.nodeId, clickInfo.requestInfo.connectRequest.pinId);

        sim_nodes[clickInfo.nodeId]->Disconnect(clickInfo.requestInfo.connectRequest.pinId, true, NODE_ID_INVALID);
        sim_nodes[outputNodeId]->Disconnect(outputPinId, false, clickInfo.nodeId);

        SimPropagateSignal(clickInfo.nodeId);
    }
}

void SimOnManagerDelete(ClickInfo_t& clickInfo)
{
    ClickInfo_t tempClickInfo;
    NodeId_t outputNodeId;
    uint8_t outputPinId;
    NodeId_t inputNodeId;
    uint8_t inputPinId;

    while (ConnFindOutputAndPin(clickInfo.nodeId, &inputPinId, &outputNodeId, &outputPinId))
    {
        ConnDelete(clickInfo.nodeId, inputPinId);

        sim_nodes[clickInfo.nodeId]->Disconnect(inputPinId, true, NODE_ID_INVALID);
        sim_nodes[outputNodeId]->Disconnect(outputPinId, false, clickInfo.nodeId);
    }
    SimPropagateSignal(clickInfo.nodeId);

    while (ConnFindInputAndPin(clickInfo.nodeId, &outputPinId, &inputNodeId, &inputPinId))
    {
        ConnDelete(inputNodeId, inputPinId);

        sim_nodes[inputNodeId]->Disconnect(inputPinId, true, NODE_ID_INVALID);
        sim_nodes[clickInfo.nodeId]->Disconnect(outputPinId, false, inputNodeId);

        SimPropagateSignal(inputNodeId);
    }

    delete sim_nodes[clickInfo.nodeId];
    sim_nodes.erase(clickInfo.nodeId);
}

void SimOnManagerMove(ClickInfo_t& internalClickInfo, const sf::Event event)
{
    sf::Vector2f tempPosition;

    tempPosition = sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y) + internalClickInfo.requestInfo.moveRequest.offset;
    sim_nodes[internalClickInfo.nodeId]->Transform(tempPosition);
    SimPropagateSignalSingleStep(internalClickInfo.nodeId);

    if (sf::Event::MouseButtonReleased == event.type)
    {
        tempPosition = sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y) + internalClickInfo.requestInfo.moveRequest.offset;
        sim_nodes[internalClickInfo.nodeId]->Transform(tempPosition);

        SimPropagateSignalSingleStep(internalClickInfo.nodeId);
        sim_state = SimulationManagerState_t::IDLE;
        memset(&internalClickInfo, 0u, sizeof(ClickInfo_t));
    }
}

void SimPropagateSignal(NodeId_t nodeId)
{
    std::list<NodeId_t> tempList;
    std::queue<NodeId_t> toEvaluate;

    toEvaluate.push(nodeId);
    while (!toEvaluate.empty())
    {
        if (sim_nodes[toEvaluate.front()]->Propagate(tempList))
        {
            while (!tempList.empty())
            {
                toEvaluate.push(tempList.front());
                tempList.pop_front();
            }
        }
        toEvaluate.pop();
    } 
}

void SimPropagateSignalSingleStep(NodeId_t nodeId)
{
    std::list<NodeId_t> tempList;
    std::queue<NodeId_t> toEvaluate;

    toEvaluate.push(nodeId);
    (void)sim_nodes[toEvaluate.front()]->Propagate(tempList);
    for (const auto& element : tempList)
    {
        toEvaluate.push(element);
    }

    while (!toEvaluate.empty())
    {
        /* tempList used as a dummy */
        (void)sim_nodes[toEvaluate.front()]->Propagate(tempList);
        toEvaluate.pop();
    } 
}
