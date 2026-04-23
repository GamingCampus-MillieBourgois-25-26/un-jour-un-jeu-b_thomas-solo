#pragma once
#include "Component.h"
class BasicBox : public Component
{
public:
	sf::RectangleShape rect;
	BasicBox(float size_x, float size_y);
	void Update(TimeModule* timeModule)override;
	void Render(WindowModule* windowModule)override;
};

