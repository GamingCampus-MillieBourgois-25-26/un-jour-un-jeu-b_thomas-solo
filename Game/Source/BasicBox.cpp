#include <Include/BasicBox.h>

BasicBox::BasicBox(float size_x, float size_y)
{
	rect.setSize({ size_x,size_y });
	rect.setOrigin(rect.getGeometricCenter());
}

void BasicBox::Update(TimeModule* timeModule)
{
	rect.setPosition(owner->GetPosition());
	rect.setScale(owner->GetScale());
	rect.setRotation(sf::degrees(owner->GetRotation()));
}

void BasicBox::Render(WindowModule* windowModule)
{
	windowModule->GetWindow()->draw(rect);
}

