#pragma once
#include "GameObject.h"
#include "Component.h"
namespace TopDown
{
	class Smoke : public GameObject
	{
	public:
		Smoke();
	};
	class SmokeMovement : public Component
	{
	public:
		float lifeTime = 3;
		float speed = 40;
		float rotateSpeed = 35;
		void Update(TimeModule* timeModule)override;
	};

}
