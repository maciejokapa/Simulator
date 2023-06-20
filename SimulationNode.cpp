#include "SimulationNode.h"

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

	result = false;

	result |= this->Clickable::IsClicked(event);
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
	window.draw(*this->shape);
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
	this->shape->setPosition(position);
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

bool SimulationNode::CommonDeleteRequest(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("imulationNode::CommonDeleteRequest\n");
	bool result;

	result = false;

	if (event.mouseButton.button == sf::Mouse::Right)
	{
		clickInfo.type = SimulationEventType_t::DELETE;
		clickInfo.nodeId = this->id;

		result = true;
		printf("TRUE\n");
	}

	return result;
}

bool SimulationNode::CommonConnectRequest(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("imulationNode::CommonConnectRequest\n");
	bool result;
	uint8_t idx;

	result = false;

	if (event.mouseButton.button == sf::Mouse::Left)
	{
		idx = 0u;
		for (const auto& input : this->simulationInputs)
		{
			if (input.IsClicked(event))
			{
				clickInfo.requestInfo.connectRequest.isInput = true;
				clickInfo.requestInfo.connectRequest.pinId = idx;
				clickInfo.requestInfo.connectRequest.pin = (void*)&input;

				result = true;
				break;
			}
			idx++;
		}

		if (!result)
		{
			idx = 0u;
			for (const auto& output : this->simulationOutputs)
			{
				if (output.IsClicked(event))
				{
					clickInfo.requestInfo.connectRequest.isInput = false;
					clickInfo.requestInfo.connectRequest.pinId = idx;
					clickInfo.requestInfo.connectRequest.pin = (void*)&output;

					result = true;
					break;
				}
				idx++;
			}
		}
	}

	if (result)
	{
		clickInfo.type = SimulationEventType_t::CONNECT;
		clickInfo.nodeId = this->id;
	}

	return result;
}

bool SimulationNode::CommonMoveRequest(sf::Event& event, ClickInfo_t& clickInfo) const
{
	printf("imulationNode::CommonMoveRequest\n");
	bool result;

	result = false;

	if (event.mouseButton.button == sf::Mouse::Left)
	{

	}

	return result;
}

