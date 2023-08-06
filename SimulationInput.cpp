#include "SimulationInput.h"
#include <SFML/Graphics/RectangleShape.hpp>

#include <cmath>
#include <stdio.h>

SimulationInput::SimulationInput(void) : Input(), SimulationPin()
{
	this->wire = nullptr;
	this->connection = nullptr;
	this->connectionSize = 0.0f;
}

void SimulationInput::Connect(SimulationOutput* connection)
{
	const float size = connection->GetSize();
	const sf::Vector2f position = connection->GetPosition();
	const sf::Vector2f offset = this->shape->getPosition() - position;
	const float length = sqrtf(offset.x * offset.x + offset.y * offset.y);

	this->Input::Connect(connection);
	this->connection = connection;
	this->connectionSize = size;
	this->wire = new SimulationWire(new sf::RectangleShape(sf::Vector2f(length, size)));

	this->wire->Transform(sf::Vector2f(position.x + size / 2, position.y + size / 2));
	this->wire->Rotate(atan2f(offset.y, offset.x) * 180.0f / (atanf(1.0) * 4));
}

void SimulationInput::UpdateWire(void)
{
	const sf::Vector2f position = this->connection->GetPosition();
	const sf::Vector2f offset = this->shape->getPosition() - position;
	const float length = sqrtf(offset.x * offset.x + offset.y * offset.y);

	this->wire->ChangeShape(new sf::RectangleShape(sf::Vector2f(length, this->connectionSize)), (this->GetState() == Pin::State_t::LOW) ? sf::Color::Red : (this->GetState() == Pin::State_t::HIGH) ? sf::Color::Green : sf::Color::Black);
	this->wire->Transform(sf::Vector2f(position.x + this->connectionSize / 2, position.y + this->connectionSize / 2));
	this->wire->Rotate(atan2f(offset.y, offset.x) * 180.0f / (atanf(1.0) * 4));
}


void SimulationInput::Disonnect(void)
{
	this->Input::Disonnect();
	delete this->wire;
}

void SimulationInput::Update(void)
{
	Pin::State_t currentState = this->GetState();

	switch (currentState)
	{
		case Pin::State_t::LOW:
		{
			this->UpdateColor(sf::Color::Red);
			break;
		}

		case Pin::State_t::HIGH:
		{
			this->UpdateColor(sf::Color::Green);
			break;
		}

		case Pin::State_t::UNDEFINED:
		{
			this->UpdateColor(sf::Color::Black);
			break;
		}
	}

	if (this->IsConnected())
	{
		this->wire->Update(currentState);
		this->UpdateWire();
	}
}

void SimulationInput::Transform(const sf::Vector2f& position) const
{
	this->SimulationPin::Transform(position);
	if (this->IsConnected())
	{
		this->wire->Transform(position);
	}
}

void SimulationInput::Draw(sf::RenderWindow& window) const
{
	this->Clickable::Draw(window);
	if (this->IsConnected())
	{
		this->wire->Draw(window);
	}
}

bool SimulationInput::IsClicked(sf::Event& event) const
{
	bool isClicked;

	isClicked = this->Clickable::IsClicked(event);
	if (this->IsConnected())
	{
		isClicked |= this->IsWireClicked(event);
	}

	return isClicked;
}

void SimulationInput::OnClick(sf::Event& event, Clickable::ClickInfo_t& clickInfo) const
{
	if (!this->IsConnected() && (event.mouseButton.button == sf::Mouse::Left))
	{
		clickInfo.type = Clickable::ClickEventType_t::CONNECT;
		clickInfo.requestInfo.connectRequest.isInput = true;
		clickInfo.requestInfo.connectRequest.pin = (void*)this;
	}
	else if (this->IsConnected() && (event.mouseButton.button == sf::Mouse::Right))
	{
		clickInfo.type = Clickable::ClickEventType_t::DISCONNECT;
		clickInfo.requestInfo.connectRequest.isInput = true;
		clickInfo.requestInfo.connectRequest.pin = (void*)this;
	}
}

bool SimulationInput::IsWireClicked(sf::Event& event) const
{
	bool isClicked;

	float xa = this->connection->GetPosition().x;
	float ya = this->connection->GetPosition().y;
	float xb = this->shape->getPosition().x;
	float yb = this->shape->getPosition().y;
	float yPos;

	float xc = (float)event.mouseButton.x;
	float yc = (float)event.mouseButton.y;

	isClicked = false;

	if ((xa <= xc) && (xc <= xb))
	{
		yPos = ((ya - yb) / (xa - xb)) * xc + (ya - ((ya - yb) / (xa - xb)) * xa) + this->connectionSize;
		if ((yPos - (this->connectionSize / 2) <= yc) && (yc <= yPos + (this->connectionSize / 2)))
		{
			isClicked = true;
		}
	}

	return isClicked;
}
