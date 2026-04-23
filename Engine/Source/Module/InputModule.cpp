#include "pch.h"
#include "Include/Engine.h"
#include "Include/Module/InputModule.h"
#include "Include/Module/WindowModule.h"
#include <iostream>
void InputModule::Start()
{
	WindowModule* windowModule = moduleManager->GetModule<WindowModule>();
	window = windowModule->GetWindow();
	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		keyUp[i] = true;
	}
	for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
		mouseUp[i] = true;
	}
}

void InputModule::Update() {
	events.clear();
	UpdatePressing();
	while (auto event = window->pollEvent())
	{
		events.push_back(*event);

		if (event->is<sf::Event::Closed>())
		{
			window->close();
			Engine::GetInstance()->Quit();
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			sf::Keyboard::Key key = keyPressed->code;
			const auto index = static_cast<unsigned int>(key);

			if (index < sf::Keyboard::KeyCount) {
				if (keyDown[index] == false) {
					keyPressing[index] = true;
				}
				keyDown[index] = true;
				keyUp[index] = false;
			}
		}
		else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			sf::Keyboard::Key key = keyReleased->code;
			const auto index = static_cast<unsigned int>(key);

			if (index < sf::Keyboard::KeyCount) {
				keyDown[index] = false;
				keyPressing[index] = false;
				keyUp[index] = true;
			}
		}
		else if (const auto* mouseButtonP = event->getIf<sf::Event::MouseButtonPressed>())
		{
			sf::Mouse::Button button = mouseButtonP->button;
			const auto index = static_cast<unsigned int>(button);

			if (index < sf::Mouse::ButtonCount) {
				if (mouseDown[index] == false) {
					mousePressing[index] = true;
				}
				mouseDown[index] = true;
				mouseUp[index] = false;

			}
		}
		else if (const auto* mouseButtonR = event->getIf<sf::Event::MouseButtonReleased>())
		{
			sf::Mouse::Button button = mouseButtonR->button;
			const auto index = static_cast<unsigned int>(button);

			if (index < sf::Mouse::ButtonCount) {
				mouseDown[index] = false;
				mousePressing[index] = false;
				mouseUp[index] = true;

			}
		}
	}

	const sf::Vector2f previous_mouse_position = sf::Vector2f(mousePosition);
	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	mouseDelta = mousePosition - previous_mouse_position;
}


bool InputModule::GetMouseButtonDown(sf::Mouse::Button button) {
	const auto index = static_cast<unsigned int>(button);

	if (index < sf::Mouse::ButtonCount) {
		return mouseDown[index];
	}
	return false;
}
bool InputModule::GetKeyDown(sf::Keyboard::Key key) {
	const auto index = static_cast<unsigned int>(key);

	if (index < sf::Keyboard::KeyCount) {
		return keyDown[index];
	}
	return false;
}
bool InputModule::GetMouseButtonUp(sf::Mouse::Button button) {
	const auto index = static_cast<unsigned int>(button);

	if (index < sf::Mouse::ButtonCount) {
		return mouseUp[index];
	}
	return false;
}
bool InputModule::GetKeyUp(sf::Keyboard::Key key) {
	const auto index = static_cast<unsigned int>(key);

	if (index < sf::Keyboard::KeyCount) {
		return keyUp[index];
	}
	return false;
}
bool InputModule::GetMouseButtonPressing(sf::Mouse::Button button)
{
	const auto index = static_cast<unsigned int>(button);

	if (index < sf::Mouse::ButtonCount) {
		return mousePressing[index];
	}
	return false;
}
bool InputModule::GetKeyPressing(sf::Keyboard::Key key)
{
	const auto index = static_cast<unsigned int>(key);

	if (index < sf::Keyboard::KeyCount) {
		return keyPressing[index];
	}
	return false;
}
sf::Vector2u InputModule::GetWindowSize()
{
	return window->getSize();
}

void InputModule::UpdatePressing()
{
	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		if (keyPressing[i]) {
			if (keyDown[i] == true) {
				keyPressing[i] = false;
			}
		}
	}
	for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
		if (mousePressing[i]) {
			if (mouseDown[i] == true) {
				mousePressing[i] = false;
			}
		}
	}
}
