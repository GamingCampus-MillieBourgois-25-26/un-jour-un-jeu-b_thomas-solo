#pragma once
#include "Include/Module.h"
#include "SFML/Graphics.hpp"
#include <string>
class WindowModule : public Module
{
	/*gere la fenentre de jeu changer la fenetre de reset son nom car sa creer une nouvelle fenetre*/
public:
	void Awake() override;
	void Clear() override;
	void Display() override;
	void SetWindowSize(sf::Vector2u size);
	void SetWindowName(std::string name);
	sf::RenderWindow* GetWindow();
private:
	sf::RenderWindow* window;
};

