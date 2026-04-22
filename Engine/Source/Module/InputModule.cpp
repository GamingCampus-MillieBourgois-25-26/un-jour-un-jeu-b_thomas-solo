#include "pch.h"
#include "Include/Engine.h"
#include "Include/Module/InputModule.h"
#include "Include/Module/WindowModule.h"
void InputModule::Start()
{
	WindowModule* windowModule = moduleManager->GetModule<WindowModule>();
	window = windowModule->GetWindow();
}

void InputModule::Update() {
	events.clear();
	for (auto& paire : mouseUp) {
		paire.second = false;
	}
	for (auto& paire : mouseDown) {
		paire.second = false;
	}
	for (auto& paire : keyUp) {
		paire.second = false;
	}
	for (auto& paire : keyDown) {
		paire.second = false;
	}
	while (auto event = window->pollEvent())
	{
		events.push_back(*event);

		if (event->is<sf::Event::Closed>())
		{
			Engine::GetInstance()->Quit();
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			keyDown[keyPressed->scancode] = true;
			keyUp[keyPressed->scancode] = false;
		}
		else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			keyDown[keyReleased->scancode] = false;
			keyUp[keyReleased->scancode] = true;
		}
		else if (const auto* mouseButtonP = event->getIf<sf::Event::MouseButtonPressed>())
		{
			mouseDown[mouseButtonP->button] = true;
			mouseUp[mouseButtonP->button] = false;
		}
		else if (const auto* mouseButtonR = event->getIf<sf::Event::MouseButtonReleased>())
		{
			mouseDown[mouseButtonR->button] = false;
			mouseUp[mouseButtonR->button] = true;
		}
	}

	const sf::Vector2f previous_mouse_position = sf::Vector2f(mousePosition);
	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	mouseDelta = mousePosition - previous_mouse_position;
}

bool InputModule::GetMouseButtonDown(sf::Mouse::Button _button) {
	return mouseDown[_button];
}
bool InputModule::GetKeyDown(sf::Keyboard::Scancode _key) {
	return keyDown[_key];
}

bool InputModule::GetMouseButtonUp(sf::Mouse::Button _button) {
	return mouseUp[_button];
}
bool InputModule::GetKeyUp(sf::Keyboard::Scancode _key) {
	return keyUp[_key];
}
sf::Vector2u InputModule::GetWindowSize()
{
	return window->getSize();
}
