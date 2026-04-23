#pragma once
#include "Include/Module.h"
#include <map>
#include <SFML/Graphics.hpp>

class InputModule : public Module
{
	/*Module de base de Engine
	recupere tout les input fait par l'utilisateur avec le clavier et la souris*/
public:
	void Start() override;
	void Update() override;

	sf::Vector2f GetMousePosition() { return mousePosition; }
	sf::Vector2f GetMouseDelta() { return mouseDelta; }

	bool GetMouseButtonDown(sf::Mouse::Button _button);
	bool GetKeyDown(sf::Keyboard::Key _key);


	bool GetMouseButtonUp(sf::Mouse::Button _button);
	bool GetKeyUp(sf::Keyboard::Key _key);


	bool GetMouseButtonPressing(sf::Mouse::Button button);
	bool GetKeyPressing(sf::Keyboard::Key key);


	const std::vector<sf::Event>& GetEvents() { return events; }
	sf::Vector2u GetWindowSize();
private:
	sf::RenderWindow* window = nullptr;

	sf::Vector2f mousePosition;
	sf::Vector2f mouseDelta;

	bool keyDown[sf::Keyboard::KeyCount] = { false };
	bool keyPressing[sf::Keyboard::KeyCount] = { false };
	bool keyUp[sf::Keyboard::KeyCount];
	bool mouseDown[sf::Mouse::ButtonCount] = { false };
	bool mousePressing[sf::Mouse::ButtonCount] = { false };
	bool mouseUp[sf::Mouse::ButtonCount];

	std::vector<sf::Event> events;

	void UpdatePressing();
};

