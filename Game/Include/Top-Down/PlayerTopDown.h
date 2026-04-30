#pragma once
#include "GameObject.h"
#include "Component.h"
#include <SpriteRender.h>
#include <InputModule.h>
#include "Include/Top-Down/TopDown.h"
#include <RessourceModule.h>
#include "CollisionBox.h"
namespace TopDown
{
	class Player : public Tank
	{
	public:
		Player(RessourceModule* ressourceModule);
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
	class CollisionBoxPlayer : public CollisionBox {
	public:
		void Collide(CollisionBox* other)override;
	};
}

