#include "SimulationNode.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

const float SimulationNode::smallestNodeSize = (float)sf::VideoMode::getDesktopMode().height / 30.0f;
const float SimulationNode::smallestPinSize = smallestNodeSize / 4.0f;

SimulationNode::SimulationNode(NodeId_t nodeId, uint16_t inLen, uint16_t outLen, float nodeSize)
	:	Clickable(new sf::RectangleShape(sf::Vector2f(nodeSize, nodeSize))),
		id(nodeId),
		simulationInputs(inLen, SimulationInput()),
		simulationOutputs(outLen, SimulationOutput())
{}

bool SimulationNode::IsClicked(sf::Event& event) const
{
	bool result;

	result = this->Clickable::IsClicked(event);
	for (const auto& input : this->simulationInputs)
	{
		result |= input.IsClicked(event);
	}
	for (const auto& output : this->simulationOutputs)
	{
		result |= output.IsClicked(event);
	}

	return result;
}

void SimulationNode::Draw(sf::RenderWindow& window) const
{
	this->Clickable::Draw(window);
	for (const auto& input : this->simulationInputs)
	{
		input.Draw(window);
	}
	for (const auto& output : this->simulationOutputs)
	{
		output.Draw(window);
	}
}

void SimulationNode::Transform(const sf::Vector2f& position) const
{
	this->Clickable::Transform(position);
	for (const auto& input : this->simulationInputs)
	{
		input.Transform(position);
	}
	for (const auto& output : this->simulationOutputs)
	{
		output.Transform(position);
	}
}

void SimulationNode::UpdatePins(void)
{
	for (auto& input : this->simulationInputs)
	{
		input.Update();
	}
	for (auto& output : this->simulationOutputs)
	{
		output.Update();
	}
}

void SimulationNode::Connect(uint8_t internalPinId, Clickable::ClickInfo_t& connectionClickInfo)
{
	if (connectionClickInfo.requestInfo.connectRequest.isInput)
	{
		this->simulationOutputs[internalPinId].Connect(connectionClickInfo.nodeId);
	}
	else
	{
		this->simulationInputs[internalPinId].Connect((SimulationOutput*)connectionClickInfo.requestInfo.connectRequest.pin);
	}
}

void SimulationNode::Disconnect(uint8_t pinId, bool isInput, NodeId_t nodeId)
{
	if (isInput)
	{
		this->simulationInputs[pinId].Disonnect();
	}
	else
	{
		this->simulationOutputs[pinId].Disonnect(nodeId);
	}
}

Clickable::ClickEventType_t SimulationNode::CommonRequest(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const
{
	bool pinsClicked;

	pinsClicked = false;
	uint8_t idx;

	idx = 0u;
	for (const auto& input : this->simulationInputs)
	{
		if (input.IsClicked(event))
		{
			input.OnClick(event, clickInfo);
			clickInfo.requestInfo.connectRequest.pinId = idx;
			clickInfo.nodeId = this->id;

			pinsClicked = true;
			break;
		}
		idx++;
	}

	if (!pinsClicked)
	{
		idx = 0u;
		for (const auto& output : this->simulationOutputs)
		{
			if (output.IsClicked(event))
			{
				output.OnClick(event, clickInfo);
				clickInfo.requestInfo.connectRequest.pinId = idx;
				clickInfo.nodeId = this->id;

				pinsClicked = true;
				break;
			}
			idx++;
		}
	}

	if (!pinsClicked)
	{
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
			{
				clickInfo.type = Clickable::ClickEventType_t::DELETE;
				clickInfo.nodeId = this->id;
			}
		}
		else if (event.mouseButton.button == sf::Mouse::Left)
		{
			clickInfo.type = Clickable::ClickEventType_t::MOVE;
			clickInfo.nodeId = this->id;
			clickInfo.requestInfo.moveRequest.orgPosition = this->shape->getPosition();
		}
	}

	return clickInfo.type;
}

