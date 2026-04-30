#pragma once
#include <GameObject.h>
#include <CollisionBox.h>
namespace TopDown
{
	class VictoryPoint : public GameObject
	{
	public:
		VictoryPoint();
	};
	class VictoryCollisionBox : public CollisionBox {
	public:
		void Collide(CollisionBox* other)override;
	};
}


