#pragma once
#include "GameObject.h"
#include <CollisionBox.h>

namespace TopDown
{
	class Obstacle : public GameObject
	{
	public:
		Obstacle(sf::Texture* tex);
	};
	class CollisionObstacle : public CollisionBox
	{
	public:
		void Collide(CollisionBox* other)override;
	};

}
