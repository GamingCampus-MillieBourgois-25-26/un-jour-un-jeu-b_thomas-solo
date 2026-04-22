#include "pch.h"
#include <iostream>
#include "Include/Component/SpriteRender.h"

void SpriteRender::LoadTexture(std::string path) {
	if (!tex.loadFromFile(path)) {
		std::cout << "error loading" << std::endl;
	}

	sprite.setTexture(tex,true);
}

SpriteRender::SpriteRender(sf::Texture* texture, sf::IntRect textureRect):sprite(tex)
{
	tex = *texture;
	SetTextureRect(textureRect);
}

void SpriteRender::Render(WindowModule* windowModule) {
	
	windowModule->GetWindow()->draw(sprite);
}

void SpriteRender::Update(TimeModule* timeModule) {
	sprite.setPosition(owner->GetPosition());
	sprite.setScale(owner->GetScale());
	sprite.setRotation(sf::degrees(owner->GetRotation() + offsetRotation));
}

void SpriteRender::Repeated() {
	tex.setRepeated(true);
	sprite.setTexture(tex, true);
}

void SpriteRender::SetTextureRect(sf::IntRect textureRect)
{
	sprite.setTextureRect(textureRect);
	sprite.setOrigin({ (float)textureRect.size.x / 2,(float)textureRect.size.y / 2 });
}
