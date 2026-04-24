#pragma once
#include "Component.h"
class Text : public Component
{
public:
	sf::Text text;
	sf::Font font;
	Text(sf::Font font);
	void Update(TimeModule* timeModule)override;
	void Render(WindowModule* windowModule)override;
};

