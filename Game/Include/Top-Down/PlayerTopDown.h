#pragma once
#include "GameObject.h"
#include "Component.h"
#include <SpriteRender.h>
#include <InputModule.h>
namespace TopDown
{
	class Player : public GameObject
	{
	public:
		float rotationBarrel = 0;
		float speed = 50;
		float rotationSpeed = 60;
		float rotationBarrelSpeed = 80;
		float reloadTime = 0;
		float reloadTimeMax = 3;
		Player();
	};
	class PlayerRender : public Component {
	public:
		Player* player = nullptr;
		SpriteRender* barrel;
		SpriteRender* frame;
		PlayerRender();
		void Start()override;
		void Update(TimeModule* timeModule)override;
		void Render(WindowModule* windowModule)override;
		void Destroy()override;

	};
	class PlayerInput : public Component {
	public:
		InputModule* input = nullptr;
		Player* player = nullptr;
		void Start()override;
		void Update(TimeModule* timeModule)override;

		void MoveForward(float speed);
		void RotateBarrel(float speedRotation);
		void Shoot();
	};
}

