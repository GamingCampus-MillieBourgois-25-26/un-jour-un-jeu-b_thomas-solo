#include "pch.h"
#include "Include/Module/TimeModule.h"

void TimeModule::Update()
{
	sf::Time delta = clock.restart();
	deltaTime = delta.asSeconds();
}
