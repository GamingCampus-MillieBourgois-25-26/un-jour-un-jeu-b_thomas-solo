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
	bool GetKeyDown(sf::Keyboard::Scancode _key);

	bool GetMouseButtonUp(sf::Mouse::Button _button);
	bool GetKeyUp(sf::Keyboard::Scancode _key);

	const std::vector<sf::Event>& GetEvents() { return events; }
	sf::Vector2u GetWindowSize();
private:
	sf::RenderWindow* window = nullptr;

	sf::Vector2f mousePosition;
	sf::Vector2f mouseDelta;

	std::map<sf::Keyboard::Scancode, bool> keyDown;
	std::map<sf::Keyboard::Scancode, bool> keyUp;
	std::map<sf::Mouse::Button, bool> mouseDown; 
	std::map<sf::Mouse::Button, bool> mouseUp;

	std::vector<sf::Event> events;
};

