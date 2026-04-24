#include <Include/Text.h>

Text::Text(sf::Font _font): font(_font), text(font)
{
	text.setCharacterSize(20);
}

void Text::Update(TimeModule* timeModule)
{
	text.setPosition(owner->GetPosition());
	text.setRotation(sf::degrees(owner->GetRotation()));
	text.setScale(owner->GetScale());
	text.setOrigin(text.getLocalBounds().getCenter());

}

void Text::Render(WindowModule* windowModule)
{
	windowModule->GetWindow()->draw(text);
}
