#pragma once
#include "Scene.h"
#include "Component.h"
#include <SpriteRender.h>
namespace TopDown
{
	class TopDown : public Scene
	{
	public:
		TopDown();
	};
	class Tank : public GameObject
	{
	public:
		float rotationBarrel = 0;
		float speed = 50;
		float rotationSpeed = 60;
		float rotationBarrelSpeed = 80;
		float reloadTime = 0;
		float reloadTimeMax = 3;
		Tank(sf::Texture* texBarrel, sf::Texture* texFrame);
	};
	class TankRender : public Component {
	public:
		Tank* tank = nullptr;
		SpriteRender* barrel;
		SpriteRender* frame;
		TankRender(sf::Texture* texBarrel, sf::Texture* texFrame);
		void Start()override;
		void Update(TimeModule* timeModule)override;
		void Render(WindowModule* windowModule)override;
		void Destroy()override;

	};
}

