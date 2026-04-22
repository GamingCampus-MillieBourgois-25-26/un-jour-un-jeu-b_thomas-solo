#pragma once
#include "Include/Module.h"
#include "SFML/System.hpp"
class TimeModule : public Module
{
	/*gere le deltaTime entre les frames*/
public:
	void Update() override;
	sf::Clock GetClock() { return clock; }
	float GetDeltaTime() { return deltaTime; }
	
private:
	sf::Clock clock;
	float deltaTime;
};

