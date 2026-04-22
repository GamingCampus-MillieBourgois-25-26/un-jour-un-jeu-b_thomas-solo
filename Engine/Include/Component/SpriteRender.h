#pragma once
#include "Include/Component.h"
#include "string"
class SpriteRender : public Component
{
	/*Component de base dans le Engine
	permet d'afficher une texture
	ka texture peut etre creer ici avec son chemin relatif ou
	utiliser avec le ressourceModule*/
public:
	sf::Texture tex;
	sf::Sprite sprite;
	SpriteRender(sf::Texture* texture, sf::IntRect textureRect);
	void LoadTexture(std::string path);
	void Repeated();
	void SetTextureRect(sf::IntRect textureRect);
	void Render(WindowModule* windowModule) override;
	void Update(TimeModule* timeModule) override;
	float offsetRotation = 0;
};

