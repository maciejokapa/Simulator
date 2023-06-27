#include "SimulationNode.h"

#include "SFML/Window/Keyboard.hpp"

#include <iostream>

const float SimulationNode::smallestNodeSize = (float)sf::VideoMode::getDesktopMode().height / 30.0f;
const float SimulationNode::smallestPinSize = smallestNodeSize / 4.0f;

SimulationNode::SimulationNode(NodeId_t nodeId, uint16_t inLen, uint16_t outLen, sf::Shape* shape, float xPos, float yPos, float size)
	:	Clickable(shape),
		id(nodeId),
		basePosition(xPos, yPos), 
		baseSize(size), 
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

SimulationEventType_t SimulationNode::CommonDeleteRequest(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("imulationNode::CommonDeleteRequest\n");
	bool pinsClicked;;

	pinsClicked = false;

	for (const auto& input : this->simulationInputs)
	{
		pinsClicked |= input.IsClicked(event);
	}
	for (const auto& output : this->simulationOutputs)
	{
		pinsClicked |= output.IsClicked(event);
	}

	if (!pinsClicked)
	{
		if ((event.mouseButton.button == sf::Mouse::Right) &&
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)))
		{
			clickInfo.type = SimulationEventType_t::DELETE;
			clickInfo.nodeId = this->id;

			printf("TRUE\n");
		}
	}

	return clickInfo.type;
}

SimulationEventType_t SimulationNode::CommonConnectRequest(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("imulationNode::CommonConnectRequest\n");
	uint8_t idx;

	if (event.mouseButton.button == sf::Mouse::Left)
	{
		idx = 0u;
		for (const auto& input : this->simulationInputs)
		{
			if (input.IsClicked(event))
			{
				input.OnClick(event, clickInfo);
				clickInfo.requestInfo.connectRequest.pinId = idx;
				clickInfo.nodeId = this->id;
				break;
			}
			idx++;
		}

		if (SimulationEventType_t::NONE == clickInfo.type)
		{
			idx = 0u;
			for (const auto& output : this->simulationOutputs)
			{
				if (output.IsClicked(event))
				{
					output.OnClick(event, clickInfo);
					clickInfo.requestInfo.connectRequest.pinId = idx;
					clickInfo.nodeId = this->id;
					break;
				}
				idx++;
			}
		}
	}

	return clickInfo.type;
}

SimulationEventType_t SimulationNode::CommonMoveRequest(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("imulationNode::CommonMoveRequest\n");
	bool pinsClicked;

	pinsClicked = false;

	for (const auto& input : this->simulationInputs)
	{
		pinsClicked |= input.IsClicked(event);
	}
	for (const auto& output : this->simulationOutputs)
	{
		pinsClicked |= output.IsClicked(event);
	}

	if (!pinsClicked)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{

		}
	}

	return clickInfo.type;
}
